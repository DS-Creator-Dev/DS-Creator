function PreEvent() {
	this.actions = []
	return this;
}

PreEvent.prototype.add = function(action) {
	this.actions.push(action);
}

PreEvent.prototype.fire = function(...args) {
	this.actions.forEach(action => action(...args));
}

module.exports = PreEvent;