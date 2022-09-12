// Tab System
const Tab = require("./tabsystem.js").Tab;
const TabsList = require("./tabsystem.js").TabsList;

module.exports = {
	add : function(title, template, data) {
		var tab = new Tab(title, template);
		tab.setData(data);
		TabsList.add(tab);
	},	
	
	remove : function(title) {
		TabsList.remove(title);
	},
	
	on : function(name, func) {
		TabsList.on(name, func);
	},
	
};