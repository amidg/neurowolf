# neurowolf
This is supposed to be powered accelerated wolf wisdom russian meme generator. Available in Telegram as @neurowolf_bot

This light-weight bot uses hardware acceleration on Intel iGPU / Arc graphics and uses the following software frameworks:
- Pillow for image generation
- [Qwen 2.5 9B with Russian dataset](hf.co/attashe/gemma-2-9b-it-russian-function-calling-GGUF-Q8_0-GGUF) for text generation
- python-telegram-bot for interactions with Telegram API
- [Intel IPEX](https://github.com/intel/ipex-llm/blob/main/docs/mddocs/Quickstart/ollama_quickstart.md)

## How to run:
1. Setup environment by posting your telegram bot token. It can be retrieved from @BotFather
```bash
export TELEGRAM_BOT_TOKEN=your:bot_token
```

2. Clone this repo and init submodules
```bash
git clone --depth=1 https://github.com/amidg/neurowolf.git
cd neurowolf
git submodule update --init
```

3. Start with container. This project was tested with Podman on Fedora systems but should be compatible with Docker as well. `sudo` is required for Intel iGPU access
```bash
sudo podman compose up -d
```
