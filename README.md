# Crypto Keychain

---

Crypto keychain shows the real time price of a specific currency


<img src="pic.jpg" width="400"/>

## Features 

- Uses websocket for the most recent price
- Can store multiple wifi networks and connect to the first available network
- Includes built-in API
- No API key needed

## Requirements

- esptool or arduino IDE

```bash
pip3 install esptool
```

## Installation

- Flashing the firmware 

    **Make sure you're using  the correct port**

    ```bash
    git clone https://github.com/polarspetroll/CryptoKeychain

    esptool.py --port PORT_NUMBER --chip esp8266 write_flash -z 0x0000 Crypto_Keychain.bin
    ```

- Configuration

    **Configuration is through the built-in API**

    1. Connect to the ESP
        ```
        SSID: Crypto Keychain
        PASSWORD: ##123CryptoKeychain123##
        ```
    
    2. Use the built-in HTTP API to change the config

        ```
        curl -X POST http://192.168.4.22/api/rewrite_config?config=JSON_CONFIG
        ```
        - Json structure for configuration
        ```json
        {
            "networks": [{"ssid": "ssid", "password": "password"}],
            "pair": "trading pair"
        }
        ```

        - available trading pairs 
            - btcusdt
            - ltcusdt
            - xmrusdt
            - xrpusdt
            - ethusdt

            **The default trading pair is btc/usdt**



