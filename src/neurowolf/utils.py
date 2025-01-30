import os

def get_env_variable(str):
    variable = os.getenv(str)
    if not variable:
        raise ValueError(
            f"Variable {variable} cannot be found")
    return variable


def get_tg_token():
    """
    Return Telegram bot token from the environment variable
    """
    return get_env_variable("TELEGRAM_BOT_TOKEN")

def get_model_name():
    return get_env_variable("LLM_MODEL")
