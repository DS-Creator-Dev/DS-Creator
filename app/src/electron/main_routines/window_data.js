// object to allow global communication between windows
let windowDataDict = {}; 

// used when passing particular parameters to create new windows
let windowDataStack = [];

module.exports = {
	"get" : function(field) { return windowDataDict[field];},
	"set" : function(field, value) { windowDataDict[field] = value; },
	"clear" : function() { windowDataDict = {}; },
	"push" : function(value) { windowDataStack.push(value); },
	"pop" : function() { return windowDataStack.pop(); }
}