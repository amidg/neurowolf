import logging
from telegram import Update
from telegram.ext import ApplicationBuilder, ContextTypes, CommandHandler

# basic logging
logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    level=logging.INFO
)

'''
    command to execute wolf meme generation
'''
async def get_standard_wolf_meme(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await context.bot.send_message(chat_id=update.effective_chat.id, text="I'm a bot, please talk to me!")

# main function
if __name__ == '__main__':
    application = ApplicationBuilder().token('TOKEN').build()
    
    # code that handles /fast_quote command that executes quote on standard image
    get_wolf_meme_handler = CommandHandler('quote', get_standard_wolf_meme)
    application.add_handler(get_wolf_meme_handler)

    # code that handles /diffusion command that executes quote on generated image
    # get_wolf_meme_handler = CommandHandler('fast_quote', get_wolf_meme)
    # application.add_handler(get_wolf_meme_handler)
    
    application.run_polling()