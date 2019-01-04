<%@ taglib uri="/WEB-INF/struts-logic.tld" prefix="logic" %>
<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>

<jsp:directive.page import="com.ja.jwmail.common.MailMessage"/>
<jsp:directive.page import="com.ja.jwmail.servlets.BaseAction"/>
<jsp:directive.page import="java.util.List"/>

<bean:define id="collectionKey" type="java.lang.String" value="<%=BaseAction.MAIL_MESSAGES%>" />
<bean:define id="contextPath" type="java.lang.String" value="<%=request.getContextPath() %>" />

<logic:notEmpty scope="session" name="<%=collectionKey%>">
 <table class="resultsTable">
 <tr>
  <th>Action</th>
  <th>From</th>
  <th>Subject</th>
  <th>Sent</th>
 </tr>

 <logic:iterate id="row" scope="session" name="<%=collectionKey%>" indexId="index">
   <bean:define id="rowClass" value="<%= ( index%2 == 0 ) ? \"even\" : \"odd\" %>" />
   <tr class="<bean:write name="rowClass"/>">
       <bean:define id="msgKey" value="messages[<%=index%>]" />
       <bean:define id="msgValue" type="java.lang.String" value="<%= ( (String)request.getParameter(msgKey) == null ) ? \"\" : \"checked\" %>" />
	   <td><input type="checkbox" name="messages[<%=index%>]" <%=msgValue%> value="on"/></td> 
	   <td><bean:write name="row" property="from"/></td> 
	   <td>
	    <span class="linkLike" onclick="getMessage('<%=contextPath%>/readMessage.do;jsessionid=<%=session.getId()%>', <%=index%>, '<bean:write name="row" property="subject"/>');">
        <bean:write name="row" property="subject"/>
	    </span>
	   </td> 
       <td><bean:write name="row" property="sentDate"/></td>  
  </tr>
 </logic:iterate> 
 </table>  
 <input type="hidden" name="count" value="<%= ((List)session.getAttribute(collectionKey)).size() %>"/>
</logic:notEmpty>
