import asyncio
from ollama import AsyncClient
from utils import get_model_name

prompt = 'Напиши абсурдную цитату про волка, которая бы была похожа на "Помни брат, что ты мне не брат, брат брат мне тот, кто брат мне брат" или "Волк слабее льва и тигра, но в цирке не выступает" или "Неважно кто волк, неважно кто лиса, важно кто насрал". Добавь что-нибудь про пиво, цирк, уличный слэнг и тому подобное. Оно может быть асбурдным по типу "Бесплатный сыр бывает только бесплатным!". Также ты можешь добавить что-нибудь по смыслу похожее на "Чтобы стать волком, не нужно думать как волк, нужно быть волком". Можно еще подумать про другие уличные высказывания по типу "Падение-это не провал, провал - это провал, падение это где упал" Ответ должен быть на русском. Максимальная длина предложения 10 слов.'

prompt_two_halves = ' Раздели созданное предложение по смыслу примерно пополам, но максимум 5 слов в каждой половине. Поставь знак % между половинами'

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
    # returns array of strings
    return result.response.split("%")
