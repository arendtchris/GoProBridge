# GoProBridge (ESP32 + Hero11)

Steuerung + Statusabfrage der GoPro Hero11 via ESP32.

## Features
- Start/Stop Recording
- Photo Trigger
- Live Status (Battery, Recording, Camera Name)
- UART Bridge Output
- JSON Status Parsing

## Struktur
- GoProAPI → HTTP Steuerung
- GoProCamera → High Level API
- StatusDecoder → Human readable Status
- CommandParser → UART Commands

## IP der GoPro
Default: 10.5.5.9
