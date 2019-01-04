<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>

<script type="text/javascript">

<!-- in ajax calls need to add in error handling with error -->

// options for all dialog boxes
var dialogOptions = { 
    width: 640, height: 480, 
    resizable: false,
    modal: 'true',
    title: '',
    buttons: { "Ok": function() { $(this).dialog("close"); } },
    close: function(event, ui) { $(this).dialog( 'destroy' ); } 
};

function getMessage(urlPrefix, msgNo, msgTitle) {

    var readurl = urlPrefix + '?index=' + msgNo;
    jQuery.ajax( { type: "GET", url: readurl,
      success: function (result) {
          // check to see if element exists else create it
          if ( $("#dialogBox").length <= 0 )  { jQuery('<div id="dialogBox"></div>').appendTo("body"); }
          $("#dialogBox").html(result);
          dialogOptions.title = 'Subject: ' + msgTitle;
          $("#dialogBox").dialog( dialogOptions );
      }
    });
    return false;
}

function deleteMessages() {

    if ( $("#alertBox").length <= 0 ) { jQuery('<div id="alertBox"></div>').appendTo("body"); }
    $("#alertBox").html("Are you sure you want to delete the selected messages?");
    dialogOptions.height = 200;
    dialogOptions.title = "Delete message(s)?"
    dialogOptions.buttons = { "Ok": function() { $(this).dialog("close"); document.forms['deleteMsg'].submit(); }, 
                      "Cancel": function() { $(this).dialog("close"); } };
    $("#alertBox").dialog( dialogOptions );
    return false;
}

function refreshInbox() { 
    var refreshurl = '<%=request.getContextPath()%>/refreshInbox.do;jsessionid=<%=session.getId()%>';
    jQuery.ajax( { type: "GET", url: refreshurl,
       success: function (result) { $("#messagesContainer").html(result); }
    });
}

function logout() { 
    var logouturl = '<%=request.getContextPath()%>/logout.do;jsessionid=<%=session.getId()%>';
    document.forms['deleteMsg'].action = logouturl;
    document.forms['deleteMsg'].submit(); 
}

function composeMessage() {

    var composeURL = '<%=request.getContextPath()%>/compose.do;jsessionid=<%=session.getId()%>';
    jQuery.ajax( { type: "GET", url: composeURL,
      success: function (result) {
          // check to see if element exists else create it
          if ( $("#composeBox").length <= 0 )  { jQuery('<div id="composeBox"></div>').appendTo("body"); }
          $("#composeBox").html(result);
          dialogOptions.title = "Compose message:"
          dialogOptions.buttons: { "Send": function() { sendMessage(); }, 
                          "Cancel": function() { $(this).dialog("close"); } }
          $("#composeBox").dialog( dialogOptions );
      }
    });
    return false;
}

function getFormElements(formName) { 

    var results = '';
    var fObj = document.forms[formName];
    var elements = fObj.elements;
    var elen = elements.length;
    for ( var i = 0; i < elen; i+=1 ) { 
        var eleObj = elements[i];
        if ( eleObj.type == 'text' ) { 
            if ( results.length > 0 ) { results += '&'; }
            results += eleObj.name + '=' + eleObj.value;
        }
    }
    return results;
}

function sendMessage() {
    var composeURL = '<%=request.getContextPath()%>/sendMessage.do;jsessionid=<%=session.getId()%>';
/*    var data = 'toUsers=' + $("#toUsersID").value
                + 'ccUsers=' + $("#ccUsersID").value 
                + 'ccUsers=' + $("#bccUsersID").value 
                + 'ccUsers=' + $("#subjectID").value 
                + 'ccUsers=' + $("#messageID").value;
*/    
    document.forms['sendmail'].submit();
} 
</script>

<div class="title">
Mail Messages
</div>
<div class="buttons">
    <button type="button" onclick="deleteMessages();">Delete</button>
    <button type="button" onclick="refreshInbox();">Refresh</button>
    <button type="button" onclick="composeMessage();">Compose</button>
    <button type="button" onclick="logout();" class="right">Logout</button>
</div>

<html:form action="/deleteMessages" onsubmit="deleteMessages();">

<div id="messagesContainer">
    <jsp:include page="refresh.jsp"/>
</div>

<div class="buttons">
    <button type="button" onclick="deleteMessages();">Delete</button>
</div>
</html:form>
