from telegram import Update
from telegram.ext import CallbackContext
from image import create_empty_image, create_image
from io import BytesIO
from ai import get_quote, get_quote_with_split

async def wolf_quote(update: Update, context: CallbackContext) -> None:
    """Handler for the /wolf command."""
    quote = await get_quote()
    await update.message.reply_text(quote)

async def wolf_picture(update: Update, context: CallbackContext) -> None:
    """
    Handler for the /wolf command
    Sends an image with text
    """
    # create BytesIO stream
    image_stream = BytesIO()
    phrases = await get_quote_with_split()
    #phrases = ["🐺 Волк пьет пиво!", "В цирке не выступает"]
    create_image(phrases, image_stream)

    # Send the image
    await update.message.reply_photo(
        photo=image_stream,
        caption=phrases[0] + " " + phrases[1])

async def empty_picture(update: Update, context: CallbackContext) -> None:
    """
    Handler for the /empty command
    Sends an image with text.
    """
    # create BytesIO stream
    image_stream = BytesIO()
    text = "🐺 The wolf howls!"
    create_empty_image(text, image_stream)
    
    # Send the image
    await update.message.reply_photo(photo=image_stream, caption="Here's a wolf message!")
