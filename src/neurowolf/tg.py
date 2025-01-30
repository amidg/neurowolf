from telegram import Update
from telegram.ext import CallbackContext
from image import create_empty_image
from io import BytesIO

async def wolf_quote(update: Update, context: CallbackContext) -> None:
    """Handler for the /wolf command."""
    await update.message.reply_text("🐺 The wolf howls at the moon!")

async def wolf_picture(update: Update, context: CallbackContext) -> None:
    """Handler for the /wolf command that sends an image with text."""
    # create BytesIO stream
    image_stream = BytesIO()
    text = "🐺 The wolf howls!"
    create_empty_image(text, image_stream)

    # Send the image
    await update.message.reply_photo(photo=image_stream, caption="Here's a wolf message!")
