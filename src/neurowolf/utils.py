import os
from os import listdir
from os.path import isfile, join

IMAGE_PATH = "./content/img/"

def get_env_variable(str):
    variable = os.getenv(str)
    if not variable:
        raise ValueError(
            f"Variable {str} cannot be found")
    return variable


def get_tg_token():
    """
    Return Telegram bot token from the environment variable
    """
    return get_env_variable("TELEGRAM_BOT_TOKEN")

def get_model_name():
    return get_env_variable("LLM_MODEL")

def get_ollama_host():
    return get_env_variable("OLLAMA_HOST")

def get_image_list():
    return [(IMAGE_PATH + f) for f in listdir(IMAGE_PATH) if isfile(join(IMAGE_PATH, f))]
