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
	
	data : function(title) {
		var tab = TabsList.find(title);
		if(tab == null) {
			alert(`Accessing data on non-existent tab : ${JSON.stringify(title)}`);
			return null;
		}
			
		if(arguments.length==1) {						
			return tab.data;
		}
		
		tab.data = arguments[1];
		return tab.data;
	},
	
	template : function(title) {
		var tab = TabsList.find(title);
		if(tab == null) {
			alert(`Accessing template on non-existent tab : ${JSON.stringify(title)}`);
			return null;
		}
		return tab.template;
	}
	
};