class Bullet {
    constructor(data = undefined) {
        if (data == undefined)
            data = {}
        this.id = data.id;
        this.owner = data.owner;
        this.x = data.x;
        this.y = data.y;
        this.direction = data.direction;
        this.speed = data.speed;

        this.timer = (new Date()).getTime()
    }
    move() {
        var now = (new Date()).getTime()
        var progress = (now - this.timer) / (serverDelay * 1000)
        this.x += Math.cos(this.direction) * this.speed * progress
        this.y += Math.sin(this.direction) * this.speed * progress
        this.timer = now
    }
}