import asyncio
import time
import random

#example of how asynchronic function work

async def count(number: int) -> int:
    print("One")
    print("Two")
    await asyncio.sleep(random.randint(1,2))
    return number-2

async def calculate_base(length: int) -> int:
    print(f"calculate_base {length}")
    return length * length

async def calculate_cube(length: int) -> int:
    result = await calculate_base(length)
    await asyncio.sleep(5)
    print(f"calculate cube")
    return result * length

async def main():
    #create the tasks and wait if all done
    #await asyncio.gather(count(),count(),count())
    task = asyncio.create_task(count(5))
    task2 = asyncio.create_task(count(4))
    task3 = asyncio.create_task(calculate_cube(3))

    #run the tasks and wait if all done
    #a = await asyncio.gather(task,task2)

    #run the task and can return one function value before end next task
    for t in asyncio.as_completed((task3,task,task2)):
        completed = await t
        print(f"Completed {completed} ")

    #print(a)



if __name__ == "__main__":
    s = time.perf_counter()
    asyncio.run(main())
    result = time.perf_counter() - s
    print(f"{__file__} executed in {result:0.3f} seconds.")



