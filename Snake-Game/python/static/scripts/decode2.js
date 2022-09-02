
function decode(buffer) {
    "use strict"
    var prefix = (new Int8Array(buffer))[0];
    var input = buffer.slice(1)
    var response, evType
    switch (prefix) {
        case 1:
            evType = "snake"
            response = decodeSnake(input)
            break;
        case 2:
            evType = "food"
            response = decodeFood(input)
            break;
        case 3:
            evType = "bullet"
            response = decodeBullet(input)
            break;
        case 4:
            evType = "border"
            response = decodeRect(input)
            break;

        case 16:
            evType = "follow"
            response = decodeInt(input)
            break;

        case 17:
            evType = "snakeTick"
            response = decodeSnakeTick(input)
            break;

        case 18:
            evType = "bulletTick"
            response = decodeBullet(input)
            break;

        case 19:
            evType = "foodTick"
            response = decodeFood(input)
            break;

        case 32:
            evType = "removeSnake"
            response = decodeInt(input)
            break;

        case 33:
            evType = "removeFood"
            response = decodeInt(input)
            break;

        case 34:
            evType = "removeBullet"
            response = decodeInt(input)
            break;

        case 48:
            evType = "youDied"
            if (input.byteLength > 0) {
                response = String.fromCharCode.apply(String, new Uint8Array(input))
            }
            break;

        case 64:
            evType = "scoreboard"
            response = decodeScoreboard(input)
            break;
    }

    return { type: evType, data: response }

    function decodeInt(arrayBuffer) {
        return new Int32Array(arrayBuffer)[0];
    }

    function decodePoint(arrayBuffer) {
        var a = new Float32Array(arrayBuffer);
        return new Point(a[0], a[1]);
    }

    function decodeRect(arrayBuffer) {
        var a = new Float32Array(arrayBuffer);
        return {
            x: a[0],
            y: a[1],
            w: a[2],
            h: a[3]
        };
    }

    function decodeFood(arrayBuffer) {
        var ints = new Int32Array(arrayBuffer);
        var floats = new Float32Array(arrayBuffer);

        return new Food({
            id: ints[0],
            x: floats[1],
            y: floats[2],
            direction: floats[3],
            speed: floats[4],
            size: floats[5]
        })
    }
    function decodeBullet(arrayBuffer) {
        var ints = new Int32Array(arrayBuffer);
        var floats = new Float32Array(arrayBuffer);

        return new Bullet({
            id: ints[0],
            owner: ints[1],
            x: floats[2],
            y: floats[3],
            direction: floats[4],
            speed: floats[5]
        })
    }

    function decodeSnakeTick(arrayBuffer) {
        var ints = new Int32Array(arrayBuffer);
        var floats = new Float32Array(arrayBuffer);

        return {
            id: ints[0],
            point: new Point(floats[1], floats[2]),
            direction: floats[3],
            size: ints[4],
            score: floats[5],
            ammo: floats[6],
            speed: floats[7]
        }
    }

    function decodeSnake(arrayBuffer) {
        var ints = new Int32Array(arrayBuffer.slice(0, 16));

        function makeString(start, length) {
            var arr = new Uint8Array(arrayBuffer.slice(start, start + length))
            var str = String.fromCharCode.apply(String, arr)
            return str
        }

        var id = ints[0]
        var name = makeString(16, ints[1])
        var skin = makeString(16 + ints[1], ints[2])
        var points = []
        for (var i = 0; i < ints[3]; i++) {
            var start = 16 + ints[1] + ints[2] + i * 8
            var p = decodePoint(arrayBuffer.slice(start, start + 8))
            points.push(p)
        }

        var buffer2 = arrayBuffer.slice(16 + ints[1] + ints[2] + ints[3] * 8)
        var ints2 = new Int32Array(buffer2);
        var floats2 = new Float32Array(buffer2);
        return new Snake({
            id: id,
            name: name,
            skin: skin,
            controlPoints: points,
            direction: floats2[0],
            size: ints2[1],
            score: floats2[2],
            bullets: floats2[3],
            speed: floats2[4]
        })
    }

    function decodeScoreboard(input) {
        function makeString(start, length) {
            var arr = new Uint8Array(input.slice(start, start + length))
            var str = String.fromCharCode.apply(String, arr)
            return str
        }

        var position = 0
        var scoreboard = []

        while (position < input.byteLength) {
            var nameLength = new Int32Array(input.slice(position, position + 4))[0]
            var score = new Float32Array(input.slice(position + 4, position + 8))[0]
            position += 8
            var name = makeString(position, nameLength)
            scoreboard.push([name,score])
            position += nameLength
        }

        return scoreboard
    }

}
