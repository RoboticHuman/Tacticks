
$("body").onload=function(){
  document.getElementById('MyTextBox').value = getDefaultPath();
  loadBehaviorModules(true);
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
    var agent = '<button type="button" class="badge" onClick="getAttr(this.id)" id="'+AgentID+'">Agent #'+ AgentID+' </p>';
    if(agent.length){
        $('<li />', {html: agent}).appendTo('ul.AgentsList')
    }
  };

  function addcheckbox(inputtext){
     var attr = inputtext
     if(attr.length){
         $('<li />', {html: attr}).appendTo('ul.AgentAttributes')
     }
   };
   function addint(inputtext){
      var attr = inputtext
      if(attr.length){
          $('<li />', {html: attr}).appendTo('ul.AgentAttributes')
      }
    };
    function addfloat(inputtext){
       var attr = inputtext;
       if(inputtext.length){
           $('<li />', {html: inputtext}).appendTo('ul.AgentAttributes')
       }
     };
     function adddropbox(inputtext){
        var attr = inputtext
        if(attr.length){
            $('<li />', {html: attr}).appendTo('ul.AgentAttributes')
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
+  $( ".AgentAttributes" ).empty();

  getAttrforAgent(currentagent);

};

/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
/*/////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*Pipeline*/
function addNewForce(forceName){
  var forceModule = forceName + '<button type="button" onClick="addForcetoPipeline(this.id)" id="'+forceName+ '" class="forcemod">'+'+'+'</button>';
  if(forceModule.length){
    $('<li />', {html: forceModule}).appendTo('ul.AvailableBehMod')
  }
}

function addNewMilestone(milestoneName){
  var milestoneModule = milestoneName + '<button type="button" onClick="addMilestonetoPipeline(this.id)" id="'+milestoneName+ '" class="milestonemod">'+'+'+'</button>';
  if(milestoneModule.length){
    $('<li />', {html: milestoneModule}).appendTo('ul.AvailableBehMod')
  }
}

function addForcetoPipeline(behName){
  elementText = behName + '<button type="button" value="-">';
  addForcetoPipeline(behName);
  if(behName.length){
    $('<li />', {html: behName}).appendTo('ul.Forces');
  }
}

function addMilestonetoPipeline(behName){
  elementText = behName + '<button type="button" value="-">';
  addForcetoPipeline(behName);
  if(behName.length){
    $('<li />', {html: behName}).appendTo('ul.Milestones');
  } else {
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

/* Checking for ints
*/
///  @param[in] evt   Keypress event
function isInt(evt) {
     evt = (evt) ? evt : window.event;
     var charCode = (evt.which) ? evt.which : evt.keyCode;
     if ((charCode !=8) && (charCode < 48 || charCode > 57)) {
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
