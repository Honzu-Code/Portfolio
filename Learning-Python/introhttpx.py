import httpx
import asyncio
import re
from collections import Counter
import cProfile
import pstats

async def calculate_https():
    websites = ["https://www.google.com"]

    async with httpx.AsyncClient() as client:
        tasks = (client.get(website) for website in websites)
        reqs = await asyncio.gather(*tasks)

    compiled = re.compile(r'\w+')
    words = [compiled.findall(req.text) for req in reqs]
    counted = [Counter(word).most_common(10) for word in words]
    print(counted)

if __name__ == "__main__":
    with cProfile.Profile() as pr:
        asyncio.run(calculate_https())
    stats = pstats.Stats(pr)
    stats.sort_stats(pstats.SortKey.TIME)
    #stats.print_stats()
