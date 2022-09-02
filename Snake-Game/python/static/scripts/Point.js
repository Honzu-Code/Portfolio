
function Point (x, y) {
    "use strict"
    this.x = x || 0
    this.y = y || 0
}

Point.prototype.distance = function (point) {
    var a = this.x - point.x
    var b = this.y - point.y
    return Math.hypot(a, b);
}
