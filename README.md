# philter
An Efficient C++ implementation of PHI detection in medical text.
It detects Protected Health Information (PHI) in clinical notes with sub-millisecond latency and zero external dependencies


**Live Endpoint**: https://zero-egress-phi.agbhat.workers.dev/scan

```
curl -X POST https://zero-egress-phi.agbhat.workers.dev/scan \
  -H "Content-Type: application/json" \
  -d '{
    "text": "Patient J0hn  (MRN: 88442211) admitted on 2024-01-05. SSN: 999-00-1234. Contact: 555-0199. Email: john.doe@gmail.com. Insurance: Member ID 998877. Account: 443322. Device MAC: 00:0a:95:9d:68:16 connected from IP 192.168.1.55. License: MD-5544. Serial No: SN-9988. Biometric data: Fingerprint scan on file. Visit https://portal.hospital.com. Zip: 01609."
  }' | json_pp
```

Output Format:

{
   "has_phi": bool,
   "detected_types": [list],
   "scan_time_ms":
}


