<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>

<jsp:directive.page import="com.ja.jwmail.servlets.BaseAction"/>

<html:errors header="errors.header" footer="errors.footer"/>

<html:form action="/sendMessage">

<ol class="formItems">
<li> 

<label> 
    <bean:message key="mail.to"/>
</label>
<html:text property="toUsers" styleId="toUsersID"/>

</li><li>

<label> 
    <bean:message key="mail.cc"/>
</label>
<html:text property="ccUsers" styleId="ccUsersID"/>

</li><li>

<label> 
    <bean:message key="mail.bcc"/>
</label>
<html:text property="bccUsers" styleId="bccUsersID"/>

</li><li>

<label> 
    <bean:message key="mail.subject"/>
</label>
<html:text property="subject" styleId="subjectID"/>

</li><li>

<label> 
    <bean:message key="mail.message"/>
</label>
<html:textarea property="message" styleId="messageID"/>

</li>
</ol>

</html:form>


