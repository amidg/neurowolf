import logging
import os
from telegram import Update
from telegram.ext import ApplicationBuilder, ContextTypes, CommandHandler

# get global variables
TELEGRAM_TOKEN = os.getenv('TELEGRAM_TOKEN')

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

async def get_diffusion_wolf_meme(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await context.bot.send_message(chat_id=update.effective_chat.id, text="Sorry, Stable Diffusion is not available yet!")

'''
extra functions
'''

# main function
if __name__ == '__main__':
    application = ApplicationBuilder().token(TELEGRAM_TOKEN).build()
    
    # code that handles /fast_quote command that executes quote on standard image
    get_wolf_meme_handler = CommandHandler('std_quote', get_standard_wolf_meme)
    application.add_handler(get_wolf_meme_handler)

    # code that handles /diffusion command that executes quote on generated image
    get_wolf_meme_diff_handler = CommandHandler('diff_quote', get_diffusion_wolf_meme)
    application.add_handler(get_wolf_meme_diff_handler)
    
    application.run_polling()