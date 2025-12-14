# MindsEye Ledger Core

`mindseye-ledger-core` is the deterministic, append-only ledger engine for MindsEye Fabric.

This repository is **integrity**, not transport.

It builds chained blocks, computes Merkle roots, and verifies ledger history.

---

## Purpose

MindsEye systems need:
- auditability
- replayability
- integrity proofs
- deterministic history

This repo provides the ledger substrate that everything else can depend on.

---

## What lives here

- Block model (`block_id`, `prev_hash`, `entries`, `ts_ms`, `merkle_root`)
- Deterministic SHA-256 hashing
- Merkle tree root computation
- Block chaining + verification
- Storage interface (memory + file implementation)

---

## What does NOT live here

- Network transport / gateways
- Google adapters
- UI rendering
- Business rules
- LLM logic

If it connects to the outside world, it does not belong here.

---

## Protocol Alignment (Mandatory)

Protocol schemas live in `mindseye-protocol` and must be included as a submodule:

```text
external/mindseye-protocol
Add it:
https://github.com/PEACEBINFLOW/mindseye-protocol/tree/main
https://github.com/PEACEBINFLOW/mindscript-runtime-c/tree/main
https://github.com/PEACEBINFLOW/mindscript-google-executor/tree/main
https://github.com/PEACEBINFLOW/mindseye-google-gateway/tree/main
https://github.com/PEACEBINFLOW/mindseye-google-auth/tree/main

