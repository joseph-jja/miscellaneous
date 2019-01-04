<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>

<jsp:directive.page import="com.ja.jwmail.servlets.BaseAction"/>
<jsp:directive.page import="java.util.List"/>
<jsp:directive.page import="com.ja.jwmail.common.MailMessage"/>

<bean:define id="msgKey" type="java.lang.String" value="<%=BaseAction.MESSAGE%>" />

<div id="resultContainer">

<html:errors header="errors.header" footer="errors.footer"/>

<logic:notEmpty scope="request" name="<%= request.getAttribute(msgKey) %>">

	<% MailMessage message = (MailMessage)request.getAttribute(msgKey); %>

<ol class="formItems">
<li> 

<label> 
	From:
</label>
<%= message.getFrom() %>

</li><li>

<label> 
	Subject: 
</label>
	<%= message.getSubject() %>
</li><li>

	<%= message.getMessageText() %>

<logic:notEmpty name="<%= message.getAttachments() %>">

    </li><li>
    
    <logic:iterate id="attachment" name="<%= message.getAttachments() %>" indexId="index">

    </logic:iterate>
    
</logic:notEmpty>

</li>
</ol>

</logic:notEmpty>

</div>
