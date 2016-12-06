
$("body").onload=function(){
  document.getElementById('MyTextBox').value = getDefaultPath();
  loadBehaviorModules();
}

/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*Sections*/
/*nav bar*/
/* Calls on function to create Folder Structure*/
 function createProjectHUD(){
      document.getElementById("saveProject").disabled = false;
      createProject(projectName);
 }
 /* Loading mesh - primtive */
  function setTextboxValue(val){
     document.getElementById("MyTextBox").value = val;
   }

   //Hide/Show functions for nav bar
   $(document).ready(function(){
     $("#hide").click(function(){
       $("#createProject").hide();
       $("#hide").hide();
       document.getElementById("saveProject").enable;
       });
       $("#show").click(function(){
           $("#createProject").show();
       });
     })

/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*Agents and Groups*/

/* add agents to the list */
 function addAgent(AgentID){
    var agent = '<button type="button" onClick="getAttr(this.id)" id="'+AgentID+'">'+ AgentID+' </p>';
    if(agent.length){
        $('<li />', {html: agent}).appendTo('ul.AgentsList')
    }
  };

  function addcheckbox(inputtext){
     var attr = inputtext
     if(attr.length){
         $('<li />', {html: agent}).appendTo('ul.AgentAttributes')
     }
   };
   function addint(inputtext){
      var attr = inputtext
      if(attr.length){
          $('<li />', {html: agent}).appendTo('ul.AgentAttributes')
      }
    };
    function addfloat(inputtext){
       var attr = inputtext
       if(attr.length){
           $('<li />', {html: agent}).appendTo('ul.AgentAttributes')
       }
     };
     function adddropbox(inputtext){
        var attr = inputtext
        if(attr.length){
            $('<li />', {html: agent}).appendTo('ul.AgentAttributes')
        }
      };

/* Placing/Editing agents toggle button */
 $(document).on('click', '.toggle-button', function() {
     $(this).toggleClass('toggle-button-selected');
     if ($(this).hasClass("toggle-button-selected")) {
       togglePlacingAgents(true);
     }else {
       togglePlacingAgents(false);
     }
 });

/* Clicking on an agent*/
function getAttr(currentagent){
  $( "#attributesList" ).empty();
  getAttrforAgent(currentagent);

};

/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*Pipeline*/
function addNewBehaviorModule(behaviordata){
  var behModule = behaviordata[0] + '<button type="button" onClick="addBehtoPipeline(this.id, this.class)" id="'+behaviordata[0]+ '" class=\"'+ behaviordata[1]'"> + </p>';
  if(behModule.length){
    $('<li />', {html: behModule}).appendTo('ul.AvailableBehMod')
  }
}
function addBehtoPipeline(behName, behType){
  behName = behName + '<button type="button"><p> - </p>';
  if (behType== "Forces"){
    addForcetoPipeline(behName);
    if(behName.length){
      $('<li />', {html: behName}).appendTo('ul.Forces');
    }
  }else {
    addMilestonetoPipeline(behName);
    if(behName.length){
      $('<li />', {html: behName}).appendTo('ul.Milestones');
    }
  }


}

//Sortable Lists
$( function() {
  $( "#Milestones" ).sortable();
  $( "#Milestones" ).disableSelection();
} );
$( function() {
  $( "#Forces" ).sortable();
  $( "#Forces" ).disableSelection();
} );
//Editing the Pipeline
var currentpipeline;
$('#Milestones input').on('click', function(e){
   $(this).parent().remove();
   //currentpipeline.updatePipeline($(this).parent());
});
$('#Forces input').on('click', function(e){
   $(this).parent().remove();
   //currentpipeline.updatePipeline($(this).parent());
});
$('#AvailableBehMod input').on('click', function(e){
        $("#Forces ul").append($("<li>").text($(this).parent().innerText));
      //  currentpipeline.updatePipeline($(this).parent());
 });

 /*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
 /*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
 /*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*Elements*/

/* When the user clicks on the button,
toggle between hiding and showing the dropdown content */
function myFunction() {
      document.getElementById("myDropdown").classList.toggle("show");
}

// Close the dropdown if the user clicks outside of it
window.onclick = function(event) {
  if (!$(event.target).hasClass("dropbtn")) {
    var dropdowns = document.getElementsByClassName("dropdown-content");
    var i;
    for (i = 0; i < dropdowns.length; i++) {
      var openDropdown = dropdowns[i];
      if (openDropdown.classList.contains('show')) {
        openDropdown.classList.remove('show');
      }
    }
  }
}
//Collapsible Lists
function toggle(elementID){
  var ele = document.getElementById(elementID);
  if (ele.style.display == "block"){
    ele.style.display = "none";
  }
  else {
    ele.style.display = "block";
  }
}

* Checking for ints
*/
///  @param[in] evt   Keypress event
function isInt(evt) {
     evt = (evt) ? evt : window.event;
     var charCode = (evt.which) ? evt.which : evt.keyCode;
     if (charCode !=8 &&)(charCode < 48 || charCode > 57)) {
         return false;
     }
     return true;
 }

 /*
 * Checking for floats
 */
 ///  @param[in] evt   Keypress event
 function isFloat(evt) {
      evt = (evt) ? evt : window.event;
      var charCode = (evt.which) ? evt.which : evt.keyCode;
      if ((charCode != 46 && charCode != 8) && (charCode < 48 || charCode > 57)) {
          return false;
      }
      return true;
  }
