# neurowolf
This is supposed to be powered accelerated wolf wisdom russian meme generator. Available in Telegram as @neurowolf_bot

This light-weight bot uses ollama python library to point to a server specified via `OLLAMA_HOST` environment variable:
- Pillow for image generation
- [gemma3:4b](https://ollama.com/library/gemma3) for text generation
- python-telegram-bot for interactions with Telegram API

## How to run:
1. Setup environment by posting your telegram bot token (can be retrieved from @BotFather) and OLLAMA_HOST
```bash
export TELEGRAM_BOT_TOKEN=your:bot_token
export OLLAMA_HOST=http://ip.of.your.server:11434
```

2. Clone this repo and init submodules
```bash
git clone --depth=1 https://github.com/amidg/neurowolf.git
cd neurowolf
git submodule update --init
```

3. Start with container. This project was tested with Podman on Fedora systems but should be compatible with Docker as well
```bash
podman-compose up -d
```
