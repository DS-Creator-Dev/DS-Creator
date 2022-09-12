"use strict";

function assert(expr){
	if(expr==true) return;	
	console.trace();
	throw "Assertion failed";
}

const Tab = require("./src/electron/preload_routines/tabsystem.js").Tab;
const TabsList = require("./src/electron/preload_routines/tabsystem.js").TabsList;

(function test_Tab(){
	console.log("Testing Tab");
	var tab1 = new Tab("tab1", "template1");	
	assert(tab1.title == "tab1");
	assert(tab1.template == "template1");	
	
	var tab2 = new Tab("tab2", "template2");
	var tab3 = new Tab("tab3", "template3");	
	
	assert(tab2.data==null);
	tab2.setData({"prop1":"val1"});
	assert(tab2.data.prop1=="val1");	

	
})();

(function test_TabsList(){
	console.log("Testing TabsList");
	var tab1 = new Tab("tab1", "template1");			
	var tab2 = new Tab("tab2", "template2");
	var tab3 = new Tab("tab3", "template3");		
	tab2.setData({"prop1":"val1"});
	
	assert(TabsList.count==0);
	
	TabsList.add(tab1);
	assert(TabsList.count==1);
	
	var tab1_clone = new Tab("tab1", "template1");				
	assert(TabsList.find("tab1") == tab1);
	assert(TabsList.find("tab1") != tab1_clone);
	tab1_clone = null;
	
	TabsList.find("tab1").data="some_data";
	assert(tab1.data=="some_data");
	
	
	TabsList.add(tab2);
	assert(TabsList.count==2);
	
	TabsList.add(tab2);
	assert(TabsList.count==2);
	
	var tab2_clone = new Tab("tab2", "template_new");
	assert(TabsList.add(tab2_clone)==false);
	assert(TabsList.find("tab2") != tab2_clone);
	assert(TabsList.find("tab2") == tab2);	
	
	TabsList.add(tab3);
	assert(TabsList.count==3);
	
	TabsList.remove(tab2);
	assert(TabsList.count==2);
	assert(TabsList.find("tab2") == null);
	assert(TabsList.find("tab1") != null);
	assert(TabsList.find("tab3") != null);
	
	TabsList.remove(tab2);
	assert(TabsList.count==2);
	
	TabsList.remove(tab1);
	assert(TabsList.count==1);
	assert(TabsList.find("tab1") == null);
	assert(TabsList.find("tab3") != null);
	
	TabsList.remove(tab3);
	assert(TabsList.count==0);
	assert(TabsList.find("tab3") == null);
	
	
})();

(function test_TabListEvents(){
	console.log("Testing TabsList PreEvents");
	
	var dummy = "";
	
	TabsList.on("tab_added", function(data){		
		dummy = data.tab.title;
	});
	
	TabsList.on("tab_removed", function(data){		
		dummy = "removed "+data.tab.title;
	});
	
	var tab1 = new Tab("tab1", "template1");			
	var tab2 = new Tab("tab2", "template2");
	var tab3 = new Tab("tab3", "template3");	
	
	dummy="";
	TabsList.add(tab1);	
	assert(dummy=="tab1");
	
	dummy="";
	TabsList.add(tab2);
	assert(dummy=="tab2");
	
	dummy="";	
	TabsList.add(tab1);	
	assert(dummy=="");
	
	dummy="";
	TabsList.remove(tab2);	
	assert(dummy=="removed tab2");
})();


console.log("Ok");