#Skull-Drop
<p align="center">
  <img src="https://github.com/FajrJauhar/Skull-Drop/blob/main/skull.png" height="300px" >
</p>

##  Skulldrop — Remote Keystroke Exfiltration Tool

> Silent. Chunked. Controlled.  
> C++ Keylogger with socket-based C2 communication and log exfiltration via file chunking.  
> Designed for research and educational use only.


## ☠️ Features

### 🎛️ Skulldrop Server (C2 — Linux)
| Feature | Description |
|--------|-------------|
| Multithreaded | Handles multiple incoming connections |
| Socket Communication | Receives data via TCP on port `8080` (configurable) |
| File Chunk Reassembly | Reconstructs log files from transmitted chunks |
| Logging | Saves logs with timestamped filenames |

---

### 👁️ Skulldrop Client (Windows)
| Feature | Description |
|--------|-------------|
| Keylogging | Captures keystrokes using `GetAsyncKeyState()` |
| Socket Transfer | Sends data to the C2 server via raw sockets |
| File Chunking | Splits log file into manageable parts for stealth transmission |
| Persistence *(Planned)* | Setup for startup persistence (optional) |
| Lightweight | Compact executable size |
| Silent Execution | No UI, no alerts (Windows Defender bypass depends on configuration) |

---

## 🧪 Project Architecture


   [Windows Client]
        ⤷ Keystrokes captured
        ⤷ Logs stored locally
        ⤷ Log split into chunks
        ⤷ Data sent via TCP sockets

             ↓

   [Linux C2 Server]
        ⤷ Listens on port 8080
        ⤷ Receives file chunks
        ⤷ Rebuilds and stores complete logs
