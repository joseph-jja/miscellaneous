<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>

<jsp:directive.page import="com.ja.jwmail.servlets.BaseAction"/>
<jsp:directive.page import="java.util.List"/>
<jsp:directive.page import="com.ja.jwmail.common.MailMessage"/>
<jsp:directive.page import="com.ja.jwmail.common.Pair"/>

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
    
    <label> 
        Attachments: 
    </label>
    <% int i = 0; %>
    <logic:iterate id="attachment" type="java.util.List" collection="<%= message.getAttachments() %>" indexId="index">
        <% List m = (List)message.getAttachments(); %>
        <% Pair p = (Pair)m.get(i); %>
        <br><%= p.getKey() %>
        <% i += 1; %>
    </logic:iterate>
    
</logic:notEmpty>

</li>
</ol>

</logic:notEmpty>

</div>
