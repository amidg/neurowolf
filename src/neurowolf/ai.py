import asyncio
from ollama import AsyncClient
from utils import get_model_name

prompt = 'Напиши абсурдную цитату про волка, которая бы была похожа на "Помни брат, что ты мне не брат, брат брат мне тот, кто брат мне брат" или "Волк слабее льва и тигра, но в цирке не выступает" или "Неважно кто волк, неважно кто лиса, важно кто насрал". Добавь что-нибудь про пиво, цирк, уличный слэнг и тому подобное. Ответ должен быть на русском. Максимальная длина предложения 10 слов. Одно предложие по типу "Бесплатный сыр бывает только бесплатным!"'

prompt_two_halves = ' Раздели созданное предложение пополам по максимум 5 слов в каждой половине и между половинами добавь знак %'

async def get_quote():
    result = await AsyncClient().generate(
        model=get_model_name(),
        prompt=prompt
    )
    return result.response

async def get_quote_with_split():
    split_prompt = prompt + prompt_two_halves
    result = await AsyncClient().generate(
        model=get_model_name(),
        prompt=split_prompt
    )
    return result.response
