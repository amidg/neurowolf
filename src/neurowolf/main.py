import os
from telegram.ext import Application, CommandHandler
from tg import wolf_quote, wolf_picture

def main():
    """
    Main function to start the bot:
    - Retrieves environment variable TELEGRAM_BOT_TOKEN
    - Starts telegram app
    """
    BOT_TOKEN = os.getenv("TELEGRAM_BOT_TOKEN")
    if not BOT_TOKEN:
        raise ValueError(
            "Bot token not found! Set TELEGRAM_BOT_TOKEN in environment variables.")

    # start Telegram app
    app = Application.builder().token(BOT_TOKEN).build()

    # Add command handler
    app.add_handler(CommandHandler("wolf", wolf_picture))
    app.add_handler(CommandHandler("quote", wolf_quote))

    # Start the bot
    print("Bot is running...")
    app.run_polling()

if __name__ == "__main__":
    main()
