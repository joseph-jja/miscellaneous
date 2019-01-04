<%@ include file="headers/htmlhead.jsp" %>

<logic:present scope="session" name="popserver">
    <% popserver.quit(); %>
    <% session.setAttribute("popserver", null); %>
</logic:present>

<%
if ( request.getSession() != null ) {
   session.invalidate();
}
%>

<P><bean:message key="logoff.message"/>

<P>Click <a href="index.jsp"><bean:message key="logoff.relogin"/></a>.

<%@ include file="footers/footer.html" %>

