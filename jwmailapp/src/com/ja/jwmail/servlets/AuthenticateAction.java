package com.ja.jwmail.servlets;

import java.io.File;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionMessage;

import com.ja.jwmail.formbeans.AuthenticationRecord;
import com.ja.jwmail.formbeans.BaseFormBean;
import com.ja.jwmail.xml.XMLConfigHandler;

/**
 * action class used to log into the pop3 server
 * 
 * @author Joseph Acosta
 *
 */
public class AuthenticateAction extends BaseAction {

	@Override
    public String processRequest(BaseFormBean  form, HttpServletRequest request,
            HttpServletResponse response, HttpSession session)
            throws Exception {

		ActionErrors errors = new ActionErrors();
		
    	// configuration file name
    	String cfgFile = "mailserver-config.xml";
    	
    	// get where we are on the file system 
    	String filePath = session.getServletContext().getRealPath(this.getClass().getName());
    	if ( filePath == null ) { 
    		errors.add("auth.error", new ActionMessage("authenticate.record.path.trans"));
    		addErrors(request, errors);
    		return BaseAction.FAILED;
    	}
    	
    	// build the file name for the config file
    	String basePathName = filePath.substring(0, filePath.indexOf(BaseAction.APPLICATION_NAME));
    	String fileName = basePathName + File.separator + BaseAction.APPLICATION_NAME 
    				+ File.separator + "WEB-INF" + File.separator + cfgFile;
    	
    	// do we have the file?
    	File configFile = new File(fileName);
    	if ( ! configFile.exists() ) { 
    		errors.add("auth.error", new ActionMessage("authenticate.record.config.exists", fileName));
    		addErrors(request, errors);
    		return BaseAction.FAILED;
    	}
    	
    	// the sax parser will read in the xml config file and parser it 
    	// all in one
    	SAXParserFactory saxFactory = SAXParserFactory.newInstance();
    	SAXParser parser = saxFactory.newSAXParser();
    	
    	// handler for the parsing
    	XMLConfigHandler handler = new XMLConfigHandler(); 
    	AuthenticationRecord authRecord = (AuthenticationRecord)form;
    	handler.setAuthRecord(authRecord);
    	
    	// actually parse the document
    	parser.parse(configFile, handler);
    	
    	// ok by here we should have a auth record in the handler
    	authRecord = handler.getAuthRecord();
    	
    	// stuff auth record in session
    	session.setAttribute(BaseAction.AUTH_RECORD, authRecord);
    	
        return BaseAction.SUCCESS;
    }
}
