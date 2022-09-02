const debuggingSnakeDrawSpeed = false

/*
 * Snake class.
 */

function Snake(data) {
    "use strict"
    var self = this
    if (data == undefined)
        data = {}

    this.id = data.id
    this.name = data.name || "Anon"
    this.controlPoints = []
    this.direction = data.direction || 0
    if (data.controlPoints)
        this.controlPoints = data.controlPoints.map(function (p) {
            return new Point(p.x, p.y)
        })
    this.length = data.size || 200
    this.skin = new Image()
    this.skin.src = data.skin || "sprites/snake1.png"
    this.skinBuffer = {
        "head": document.createElement("canvas"), // NxN
        "body": document.createElement("canvas"), // NxY
        "tail": document.createElement("canvas") // NxN
    }
    this.ctx = document.createElement("canvas").getContext("2d")

    this.score = data.score || 0
    this.bullets = data.bullets || 0
    this.speed = data.speed || 0
    this.lastUpdate = (new Date()).getTime()

    // TODO use lastUpdate, speed and more in draw function
    // to draw supposed position based on direction
    // after(if) we add rotationSpeed

    if (self.skin.width)
        setSkinBuffer()
    this.skin.addEventListener("load", setSkinBuffer)
    function setSkinBuffer() {
        var head = self.skinBuffer.head.getContext("2d")
        var body = self.skinBuffer.body.getContext("2d")
        var tail = self.skinBuffer.tail.getContext("2d")
        var w = self.skin.naturalWidth
        var h = self.skin.naturalHeight
        head.canvas.width = h
        head.canvas.height = h
        tail.canvas.width = h
        tail.canvas.height = h
        body.canvas.width = w - 2 * h
        body.canvas.height = h

        head.drawImage(self.skin, w - h, 0, h, h, 0, 0, h, h)
        body.drawImage(self.skin, h, 0, w - 2 * h, h, 0, 0, w - 2 * h, h)
        tail.drawImage(self.skin, 0, 0, h, h, 0, 0, h, h)
    }
}

Snake.prototype.draw = function (ctx2, ofX, ofY) {
    "use strict"
    var self = this
    var p = this.controlPoints
    if (p.length < 2)
        return;

    if (debuggingSnakeDrawSpeed) {
        console.time("snake draw")
        console.time("snake pre-draw")
    }

    var ctx = this.ctx
    ctx.canvas.width = ctx2.canvas.width
    ctx.canvas.height = ctx2.canvas.height
    ctx.clearRect(0, 0, ctx.canvas.width, ctx.canvas.height)
    ctx.save()
    ctx.translate(ofX, ofY)

    var head = self.skinBuffer.head
    var body = self.skinBuffer.body
    var tail = self.skinBuffer.tail
    var h = body.height
    var w = body.width

    ctx.strokeStyle = this.skin
    var bram = 0

    if (debuggingSnakeDrawSpeed) {
        console.timeEnd("snake pre-draw")
        console.time("snake draw-body")
    }

    ctx.globalCompositeOperation = "destination-over"
    for (var i = 1; i < p.length; i++) {
        var v = [p[i].x - p[i - 1].x, p[i].y - p[i - 1].y]
        var r = Math.atan2(v[1], v[0])
        var x = Math.hypot(v[0], v[1])
        ctx.save()
        ctx.translate(p[i - 1].x, p[i - 1].y)
        ctx.rotate(r)
        var l = x + h / 2;
        while (l > 0) {
            var d = Math.min(l, w - bram % w)
            ctx.drawImage(body,
                Math.round(bram % w), 0, Math.round(d), Math.round(h),
                Math.round(x - l), Math.round(h * -0.5), Math.round(d), Math.round(h))
            bram += d
            l -= d
        }
        bram -= h / 2
        ctx.restore()
    }

    if (debuggingSnakeDrawSpeed) {
        console.timeEnd("snake draw-body")
        console.time("snake draw-border")
    }

    ctx.globalCompositeOperation = "destination-in"
    ctx.strokeStyle = "white"
    ctx.beginPath()
    ctx.lineJoin = 'round';
    ctx.moveTo(p[0].x, p[0].y)
    for (var i = 1; i < p.length; i++)
        ctx.lineTo(p[i].x, p[i].y)
    ctx.lineWidth = h
    ctx.stroke();
    ctx.globalCompositeOperation = "destination-over"
    ctx.lineWidth += 2
    ctx.stroke();

    if (debuggingSnakeDrawSpeed) {
        console.timeEnd("snake draw-border")
        console.time("snake draw-head_and_tail")
    }

    ctx.globalCompositeOperation = "source-over"
    ctx.save()

    var v2 = [p[1].x - p[0].x, p[1].y - p[0].y]
    ctx.translate(p[0].x, p[0].y)
    ctx.rotate(Math.atan2(v2[1], v2[0]))
    ctx.drawImage(tail, -h, -h / 2, h, h)

    ctx.restore()
    ctx.save()
    var v3 = [p[p.length - 1].x - p[p.length - 2].x, p[p.length - 1].y - p[p.length - 2].y]
    ctx.translate(p[p.length - 1].x, p[p.length - 1].y)
    ctx.rotate(Math.atan2(v3[1], v3[0]))
    ctx.drawImage(head, 0, -h / 2, h, h)

    if (debuggingSnakeDrawSpeed) {
        console.timeEnd("snake draw-head_and_tail")
        console.time("snake draw-text")
    }

    var text = this.score ? "Score: " + Math.round(this.score) : ""
    var text2 = this.bullets ? "Bullets: " + this.bullets : ""

    ctx.fillStyle = "#0ff"
    ctx.textAlign = "right"
    ctx.fillText(text, 0, -h)

    ctx.save()
    ctx.textAlign = "left"
    ctx.fillStyle = "#0ff"
    ctx.rotate(Math.PI)
    ctx.fillText(text2, 0, -h)
    ctx.restore()

    ctx.restore()
    if (debuggingSnakeDrawSpeed) {
        console.timeEnd("snake draw-text")
    }

    ctx.restore()

    if (debuggingSnakeDrawSpeed) {
        console.timeEnd("snake draw")
        console.log(0, "-----------------------------")
    }
}


Snake.prototype.cutToSize = function () {
    "use strict"
    var self = this
    var p = self.controlPoints

    if (p.length < 2) {
        console.log("This snake has less than one line.")
        return;
    }

    function getOversize() {
        var c = 0
        for (var i = 1; i < p.length; i++) {
            c += p[i].distance(p[i - 1])
        }
        return Math.round(Math.max(0, c - self.length))
    }
    var s = getOversize()
    while (s) {
        var v = [p[1].x - p[0].x, p[1].y - p[0].y]
        var d = Math.hypot(v[0], v[1])
        var a = Math.atan2(v[1], v[0])
        d = Math.max(0, d - s)

        p[0].x = p[1].x - Math.round(d * Math.cos(a))
        p[0].y = p[1].y - Math.round(d * Math.sin(a))

        while (p[0].x == p[1].x && p[0].y == p[1].y)
            p.splice(0, 1)
        s = getOversize()
    }
}

Snake.prototype.tick = function () {
    this.cutToSize()
}
