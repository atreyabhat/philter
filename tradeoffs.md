**What approaches were used? Why?**
1. Chose Google's RE2 instead of standard regex library in C++. It is recommended for high-safety tasks and is linear-time O(n) execution.
2. std::string_view instead of std::string. This loads the string into buffer wthout copying.
3. This efficient approach can scan a 10KB text in under 10ms.
4. I benchmarked this against a "dslim/bert-base-NER" Transformer model running on a local GPU (Mac MPS). While the Transformer offered better semantic understanding, it required 300ms+ per request.
   

**Which identifier types were skipped or handled poorly? Why?**

Vehicle license plates were handled poorly as they vary geographically and custom plates are hard to identify without knowing the context.


**What adversarial patterns would bypass the detector?**

It is observed that Names with typos can be missed (J0hn instead of John). This is pure regex pattern matching error. 
These can be handled by writing multiple combination of regex patterns but can become extensive and hard to maintain.


**What more can we do with a GPU/more time?**

The focus was on reducing latency and High Recall / Low Precision. I considered false positives to be better than having false negatives.
We can block it first as a precaution and then use a hybrid ML and generalizable detector to handle fuzzy entities. 

Layer 1 Current C++: Fast, blocking gatekeeper.
Layer 2: A Transformer-based model to handle fuzzy entities.
Custom Fine-tuning: Standard BERT models perform poorly on Dates and SSNs. I would fine-tune a model specifically for medical de-identification.
Optimization: ONNX runtime and quantization to reduce inference time.

Bonus: Generative AI often outputs data in Base64 or other encodings. 
An ML model could be trained to detect potential encoded PHI that a regex would miss, preventing upload to external LLMs.

With more time, I would implement a formal Evaluation Pipeline using labeled ground-truth datasets. 
This would allow us to generate precision/recall curves for each regex pattern, identifying exactly where the approach fails against real-world clinical noise.

I skimmed through these papers with novel methods implemented in the deidentification domain including CRFs, Token classiification techniques which can be used for a hybrid model. 

[Automatic de-identification of textual documents in the electronic health record: a review of recent research](https://link.springer.com/article/10.1186/1471-2288-10-70)
[A hybrid approach to automatic de-identification of psychiatric notes](https://clamp.uth.edu/challenges-publications/A%20hybrid%20approach%20to%20automatic%20de-identification%20of%20psychiatric%20notes.pdf)
