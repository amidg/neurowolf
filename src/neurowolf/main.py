from telegram.ext import Application, CommandHandler
from tg import wolf_quote, wolf_picture
from utils import get_tg_token

def main():
    """
    Main function to start the bot:
    - Retrieves environment variable TELEGRAM_BOT_TOKEN
    - Starts telegram app
    """
    BOT_TOKEN = get_tg_token()

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
