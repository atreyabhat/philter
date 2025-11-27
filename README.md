# Philter

**Philter** is an efficient C++ implementation of PHI (Protected Health Information) detection in medical text, compiled to WebAssembly for Cloudflare Workers. It detects HIPAA Safe Harbor identifiers in clinical notes with sub-millisecond latency and zero external dependencies.

## Live Endpoint

**URL:** `https://zero-egress-phi.agbhat.workers.dev/scan`

### Example Usage

```bash
curl -X POST https://zero-egress-phi.agbhat.workers.dev/scan \
  -H "Content-Type: application/json" \
  -d '{
    "text": "Patient J0hn  (MRN: 88442211) admitted on 2024-01-05. SSN: 999-00-1234. Contact: 555-0199. Email: john.doe@gmail.com. Insurance: Member ID 998877. Account: 443322. Device MAC: 00:0a:95:9d:68:16 connected from IP 192.168.1.55. License: MD-5544. Serial No: SN-9988. Biometric data: Fingerprint scan on file. Visit https://portal.hospital.com. Zip: 01609."
  }' | json_pp
```

### Output Format

```json
{
   "has_phi": true,
   "detected_types": [
      "ACCOUNT",
      "BIOMETRIC",
      "DATE",
      "DEVICE_ID",
      "EMAIL",
      "HEALTH_PLAN",
      "IP_ADDRESS",
      "MRN",
      "NAME",
      "PHONE",
      "SERIAL",
      "SSN",
      "URL",
      "ZIP_CODE"
   ],
   "scan_time_ms": 1
}
```

## Implementation Details

*   **Core Logic:** C++ compiled to WebAssembly.
*   **Regex Engine:** [Google RE2](https://github.com/google/re2) (guarantees linear time execution).
*   **Regex Patterns:** borrowed from [Microsoft Presidio](https://github.com/microsoft/presidio)
*   **Performance:** <40ms latency on 10KB data (P95).
*   **Privacy:** Zero egress. No data leaves the worker instance except the response.

## Prerequisites

*   [Emscripten (emsdk)](https://emscripten.org/docs/getting_started/downloads.html)
*   [Node.js & NPM](https://nodejs.org/)
*   [Wrangler](https://developers.cloudflare.com/workers/wrangler/install-and-update/)


## Build & Run

### Build
You can build the project with the provided script. This will fetch and compile RE2 (if needed) and compile the C++ scanner to WebAssembly.

```bash
./build.sh
```

### Run Locally

```bash
npx wrangler dev
```
