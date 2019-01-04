package com.ja.jwmail.servlets;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.ja.jwmail.formbeans.BaseFormBean;

/**
 * this is the base action class that should do most of what struts expects
 * the idea here is that this class could be swapped out and 
 * the child classes would need little or no changes
 * 
 * @author Joseph Acosta
 */
public abstract class BaseAction extends Action {

	public static final String APPLICATION_NAME = "jwmailapp";
	
    public static final String SUCCESS = "success";
    public static final String FAILED = "failed";

    // we stuff the messages in the session
    public static final String AUTH_RECORD = "authenticationRecordString";
    public static final String MAIL_MESSAGES = "pop3MailMessagesString";
    public static final String MESSAGE = "pop3MessageString";
    
    /**
     * This is the action called from the Struts framework.
     * 
     * @param mapping The ActionMapping used to select this instance.
     * @param form The optional ActionForm bean for this request.
     * @param request The HTTP Request we are processing.
     * @param response The HTTP Response we are processing.
     * @throws java.lang.Exception
     * @return
     */
    public ActionForward execute(ActionMapping mapping, ActionForm  form,
            HttpServletRequest request, HttpServletResponse response)
            throws Exception {

        HttpSession session = request.getSession();

        BaseFormBean bfb = (BaseFormBean)form;

        String fwd = processRequest(bfb, request, response, session);

        return mapping.findForward(fwd);
    }

    /**
     * check a string to make sure it has text
     * @param in
     * @return
     */
	public static final boolean hasText(String in) { 
		
		if ( in == null || in.length() < 1 ) { 
			return false;
		}
		
		return true;
	}
	
    public abstract String processRequest(BaseFormBean  form, HttpServletRequest request,
            HttpServletResponse response, HttpSession session)
            throws Exception;

}
