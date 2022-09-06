
const consoleLogRedrawTime = false

/*
 * GUI Engine
 */

function Game(container, socket, onDeath) {
    "use strict"
    var self = this
    this.alive = false
    this.ctx = document.createElement("canvas").getContext("2d")
    container.appendChild(this.ctx.canvas)
    this.snakes = {}
    this.follow = 0
    this.needsRedraw = true
    this.food = {}
    this.bullets = {}
    this.direction = 0
    this.lastCameraX = 0
    this.lastCameraY = 0
    this.onDeath = onDeath;
    this.container = container
    this.respawn = () => {
        self.alive = true;
	if(socket.readyState !== 1)
	    location.reload();
        socket.send("respawn")
        console.log("Player respawns")
    }
    self.border = undefined

    socket.binaryType = "arraybuffer"

    Object.defineProperty(this, "offsetX", {
        get: function () {
            var snake = this.snakes[self.follow]
            if (!snake || !snake.controlPoints.length)
                return this.lastCameraX
            var p = snake.controlPoints
            var x = this.ctx.canvas.width / 2 - p[p.length - 1].x
            this.lastCameraX = x
            return x
        }
    })
    Object.defineProperty(this, "offsetY", {
        get: function () {
            var snake = this.snakes[self.follow]
            if (!snake || !snake.controlPoints.length)
                return this.lastCameraY
            var p = snake.controlPoints
            var y = this.ctx.canvas.height / 2 - p[p.length - 1].y
            this.lastCameraY = y
            return y
        }
    })

    // https://gist.github.com/72lions/4528834
    var _appendBuffer = function (buffer1, buffer2) {
        var tmp = new Uint8Array(buffer1.byteLength + buffer2.byteLength);
        tmp.set(new Uint8Array(buffer1), 0);
        tmp.set(new Uint8Array(buffer2), buffer1.byteLength);
        return tmp.buffer;
    };

    this.send = function (code, arrayBuffer) {
        if (socket.readyState !== 1 || !this.alive)
            return;
        var str = new ArrayBuffer(1)
        var strV = new Uint8Array(str)
        strV[0] = code.charCodeAt(0)
        if (arrayBuffer != undefined) {
            socket.send(_appendBuffer(strV.buffer, arrayBuffer))
        } else {
            socket.send(str)
        }
    }

    setInterval(function () {
        var ok = true
        if (self.ctx.canvas.width !== container.offsetWidth)
            ok = false
        if (self.ctx.canvas.height !== container.offsetHeight)
            ok = false

        if (!ok) {
            self.ctx.canvas.width = container.offsetWidth
            self.ctx.canvas.height = container.offsetHeight
            self.requestRedraw()
        }
    }, 30)

    socket.addEventListener("message", function (event) {
        //console.time("recvMsg")
        self.messageHandler(decode(event.data))
        //console.timeEnd("recvMsg")
    })

    var i = 0
    var fpsCounter = []
    function anima() {
        window.requestAnimationFrame(anima)
        self.tick(i++)
        self.redraw()

        /*
         var now = (new Date()).getTime()
         fpsCounter.push(now)
         if (i % 120 == 0) {
         while (fpsCounter[0] < now - 1000) {
         fpsCounter.shift()
         }
         console.log("FPS:", fpsCounter.length)
         }*/
    }
    window.requestAnimationFrame(anima)

    this.initUserControls()
}

Game.prototype.requestRedraw = function () {
    this.needsRedraw = true
}
Game.prototype.messageHandler = function (message) {
    "use strict"
    var self = this
    var data = message.data
    switch (message.type) {
        case "snake":
            if (self.snakes[data.id]) {
                self.container.removeChild(self.snakes[data.id].ctx.canvas)
            }
            self.snakes[data.id] = data
            self.container.appendChild(data.ctx.canvas)
            break;
        case "food":
            self.food[data.id] = data
            break;
        case "bullet":
            self.bullets[data.id] = data
            break;

        case "foodTick":
            if (self.food[data.id] != undefined)
                self.food[data.id] = data
            break;

        case "bulletTick":
            if (self.bullets[data.id] != undefined)
                self.bullets[data.id] = data
            break;

        case "follow":
            self.follow = data
            break;
        case "border":
            self.border = data
            break;

        case "snakeTick":
            var snake = self.snakes[data.id]
            if (!snake)
                break;
            snake.controlPoints.push(data.point)
            snake.direction = data.direction
            snake.length = data.size
            snake.score = data.score
            snake.bullets = data.ammo
            snake.speed = data.speed
            break;

        case "removeSnake":
            var id = data
            if (self.snakes[id])
                self.container.removeChild(self.snakes[id].ctx.canvas)
            delete self.snakes[id]
            break;
        case "removeFood":
            delete self.food[data]
            break;
        case "removeBullet":
            delete self.bullets[data]
            break;

        case "youDied":
            this.alive = false
            this.snakes = {}
            this.bullets = {}
            this.food = {}
            self.onDeath(data)
            while (self.container.firstChild)
                self.container.removeChild(self.container.firstChild)
            self.container.appendChild(self.ctx.canvas)
            console.log("Player died")
            break;

        case "scoreboard":
            var newData = data.sort((a, b) => {
                if (a[1] > b[1]) return -1
                if (a[1] < b[1]) return 1
                return 0
            })
            this.updateScoreboard(newData)
            break;

        default:
            console.log("Not implemented event handler:", message.type);
            break;
    }
    this.requestRedraw();
}


Game.prototype.redraw = function () {
    "use strict"
    var self = this
    var ctx = this.ctx
    var w = ctx.canvas.width
    var h = ctx.canvas.height

    if (consoleLogRedrawTime)
        console.time("draw")

    if (consoleLogRedrawTime)
        console.time("clear & background")
    ctx.clearRect(0, 0, w, h)
    ctx.save()
    if (true) { // draw background
        var size = 256
        var a = self.offsetX % size
        var b = self.offsetY % size
        ctx.beginPath()
        ctx.strokeStyle = "#000";
        for (var i = a; i < a + w + size; i += size) {
            ctx.moveTo(i, 0)
            ctx.lineTo(i, h)
        }
        for (var i = b; i < b + h + size; i += size) {
            ctx.moveTo(0, i)
            ctx.lineTo(w, i)
        }
        ctx.stroke()
    }

    ctx.translate(this.offsetX, this.offsetY)

    if (self.border !== undefined) {
        var b = self.border
        ctx.beginPath()
        ctx.moveTo(b.x, b.y)
        ctx.lineTo(b.x + b.w, b.y)
        ctx.lineTo(b.x + b.w, b.y + b.h)
        ctx.lineTo(b.x, b.y + b.h)
        ctx.lineTo(b.x, b.y)
        ctx.strokeStyle = "#f00"
        ctx.stroke()
    }
    if (consoleLogRedrawTime)
        console.timeEnd("clear & background")

    if (consoleLogRedrawTime)
        console.time("food & bullets")
    ctx.fillStyle = "#0ff"
    Object.values(this.food).forEach(function (dot) {
        if (dot == undefined)
            return;
        ctx.beginPath()
        var size = dot.size - 1 + 2 * Math.abs((dot.x + dot.y) % 50 - 25) / 25
        ctx.arc(dot.x, dot.y, Math.round(size), 0, 2 * Math.PI)
        ctx.fill()
    })

    ctx.fillStyle = "#e9db11"
    Object.values(this.bullets).forEach(function (bullet) {
        ctx.beginPath()
        var size = 3.5
        ctx.arc(bullet.x, bullet.y, Math.round(size), 0, 2 * Math.PI)
        ctx.fill()
    })
    if (consoleLogRedrawTime)
        console.timeEnd("food & bullets")


    ctx.restore()

    if (self.needsRedraw) {
        if (consoleLogRedrawTime)
            console.time("snakes")

        Object.values(this.snakes).forEach(function (snake) {
            snake.tick()
            snake.draw(self.ctx, self.offsetX, self.offsetY)
        })
        self.needsRedraw = false

        if (consoleLogRedrawTime)
            console.timeEnd("snakes")
    }

    if (consoleLogRedrawTime)
        console.timeEnd("draw")
}

Game.prototype.addSnake = function (snake) {
    this.snakes.push(snake)
}

Game.prototype.tick = function (i) {
    if (i % 2 === 0) {
        var deltaDirection = this.lastDirection - this.direction
        if (isNaN(deltaDirection) || Math.abs(deltaDirection) > 0.02) {
            var direction = new Float32Array(1);
            direction[0] = this.direction
            this.send("d", direction.buffer)
            this.lastDirection = this.direction;
        }
    }
    // console.time("math")
    for (var key in this.bullets)
        this.bullets[key].move()
    for (var key in this.food) // implement food dodge
        this.food[key].move()
    // console.timeEnd("math")

}

Game.prototype.initUserControls = function () {
    "use strict"
    var self = this

    var c = this.container
    c.addEventListener("mousemove", function (e) {
        var snake = self.snakes[self.follow]
        if (!snake || !snake.controlPoints.length)
            return 0
        var p = snake.controlPoints
        var a = p[p.length - 1]

        var y = e.offsetY - self.offsetY - a.y
        var x = e.offsetX - self.offsetX - a.x
        self.direction = Math.atan2(y, x)
    })

    c.addEventListener("click", function (e) {
        self.send("s") // shoot
    })
}

Game.prototype.updateScoreboard = function (data) {
    var client = this
    var self = this.updateScoreboard
    if (self.div === undefined) {
        self.div = document.createElement("div")
        self.div.setAttribute("id", "scoreboard")
    }
    if (!this.container.contains(self.div) && this.alive) {
        this.container.appendChild(self.div)
    }
    while (self.div.firstChild)
        self.div.removeChild(self.div.firstChild)

    var header = document.createElement("span")
    header.setAttribute("id", "scoreboardHeader")
    header.innerText = "Scoreboard"
    self.div.appendChild(header)

    data.forEach(function (pair, place) {
		var name = pair[0]
		var score = pair[1]
        var player = client.snakes[client.follow]
        if (place >= 10) {
            if (!player || name != player.name) {
                console.log(playerName)
                return;
            }
        }
        var container = document.createElement("div")
        if (player && name == player.name) {
            container.setAttribute("id", "scoreboardYou")
        }
        var right = document.createElement("span")
        var left = document.createElement("span")
        container.innerText = name
        container.appendChild(left)
        left.style.float = "left"
        left.innerText = place + 1 + "."
        left.style.marginRight = "5px"
        container.appendChild(right)
        right.style.float = "right"
        right.innerText = score
        self.div.appendChild(container)
    })

}
