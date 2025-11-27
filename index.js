import ModuleFactory from './worker.js';
import wasmModule from './worker.wasm';

let philterInstance = null;

async function getPhilter() {
  if (philterInstance) return philterInstance;

  const module = await ModuleFactory({
    instantiateWasm: (imports, successCallback) => {
      WebAssembly.instantiate(wasmModule, imports)
        .then((instance) => {
          successCallback(instance);
        })
        .catch((err) => {
          console.error("WASM instantiation failed", err);
        });
      return {}; 
    }
  });

  // Match the Class Name defined in EMSCRIPTEN_BINDINGS
  philterInstance = new module.Philter();
  return philterInstance;
}

export default {
  async fetch(request, env, ctx) {
    if (request.method !== "POST") {
      return new Response("Method not allowed", { status: 405 });
    }

    try {
      const { text } = await request.json();
      const start = performance.now();

      const scanner = await getPhilter();
      
      // Match the function name defined in C++ (.function("filter", ...))
      const result = scanner.filter(text || "");

      // Handle the Vector Proxy (Memory Management)
      const detectedTypes = [];
      if (result.detected_types && result.detected_types.size) {
        for (let i = 0; i < result.detected_types.size(); i++) {
          detectedTypes.push(result.detected_types.get(i));
        }
        // CRITICAL: Delete the C++ vector to free memory
        result.detected_types.delete();
      }

      const end = performance.now();

      return new Response(JSON.stringify({
        has_phi: result.has_phi,
        detected_types: detectedTypes,
        scan_time_ms: Math.round(end - start)
      }), {
        headers: { "Content-Type": "application/json" }
      });

    } catch (e) {
      return new Response(JSON.stringify({ error: e.message }), { status: 500 });
    }
  }
};