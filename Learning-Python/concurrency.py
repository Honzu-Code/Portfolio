#
import requests
import multiprocessing
import time

import asyncio
import aiohttp

#the best for I/O bound
#async def download_site(session, url):
#    async with session.get(url) as response:
#        print("Read {0} from {1}".format(response.content_length, url))
#
#
#async def download_all_sites(sites):
#    async with aiohttp.ClientSession() as session:
#        tasks = []
#        for url in sites:
#            task = asyncio.ensure_future(download_site(session, url))
#            tasks.append(task)
#        await asyncio.gather(*tasks, return_exceptions=True)
#
#
#if __name__ == "__main__":
#    sites = [
#        "https://www.jython.org",
#        "http://olympus.realpython.org/dice",
#    ] * 80
#    start_time = time.time()
#    asyncio.get_event_loop().run_until_complete(download_all_sites(sites))
#    duration = time.time() - start_time
#    print(f"Downloaded {len(sites)} sites in {duration} seconds")


#the best for calculate bound
def cpu_bound(number):
    return sum(i * i for i in range(number))


def find_sums(numbers):
    with multiprocessing.Pool() as pool:
        pool.map(cpu_bound,numbers)


if __name__ == "__main__":
    numbers = [5_000_000 + x for x in range(20)]
    start_time = time.time()
    find_sums(numbers)
    duration = time.time() - start_time
    print(f"Duration {duration} seconds")
