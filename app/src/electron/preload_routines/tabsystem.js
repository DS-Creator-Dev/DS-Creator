"use strict";

var PreEvent = require("./event.js");

var TabsList = (function() {
	var self = this;
	var __list = [];
	
	var ev = {};
	
	function add_event(name, action) {
		if(!(name in ev)) {
			ev[name] = new PreEvent();
		}
		ev[name].add(action);
	}
	
	function trigger_event(name, ...args) {
		console.log(ev);
		if(name in ev) {
			ev[name].fire(...args);
		}
	}	
	
	return {		
		"add" : function(tab) {
			var target = this.find(tab.title);
			if(target==null) {
				__list.push(tab);				
				trigger_event("tab_added", {"tab":tab});
				return true; // tab successfully added
			}
			else {
				return false; // tab already exists
			}
		},				
		
		"find" : function(title) {
			var subjects = __list.filter(t=> t.title == title);
			if(subjects.length==0) 
				return null;
			if(subjects.length>1) {
				throw "Duplicate tab titles!!!";
			}	
			return subjects[0];
		},		
		
		"on" : function(name, action) {
			add_event(name, action);
		},
		
		"remove" : function(tab) {
			var target = this.find(tab.title);
			if(target==null) {
				return;
			}
			trigger_event("tab_removed", {"tab":target});
			__list = __list.filter(t=> t.title != tab.title);			
		},
		
		get count() { return __list.length; },
		
	};
})();

function Tab(title, template) {
	this.title = title;
	this.template = template;
	this.data = null;	
	
	return this;
}

Tab.prototype.setData = function(data) {
	this.data = data;
}

module.exports = {
	"Tab" : Tab,
	"TabsList" : TabsList
};