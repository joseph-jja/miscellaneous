<%@ taglib uri="/WEB-INF/struts-bean.tld" prefix="bean" %>
<%@ taglib uri="/WEB-INF/struts-html.tld" prefix="html" %>


<html:errors header="errors.header" footer="errors.footer"/>

<html:form action="/auth" method="POST" focus="username">

<ol class="formItems">
<li> 

<label> 
	<bean:message key="username"/>
</label>
<html:text property="username"/>

</li><li>

<label>
	<bean:message key="password"/>
</label>
<html:password property="password"/>

</li>
</ol>

<div class="buttons">
	<button type="submit" name="submit">
		<bean:message key="logon.button"/>
	</button>
</div>

</html:form>


