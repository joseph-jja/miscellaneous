package com.ja.jwmail.common;


import java.lang.String; 

public class URLString {

     // this is a list of stop codes for a URL i.e. 
     // they cannot appear in a URL according to RFC 1738
     // Q: do we need to worry about : and ? 
     private static final String[] urlEscCodes = {  " ", "<", ">", "\"", 
                                    "#", "%", "{", "}", "|", "\\", "^", 
                                    "[", "]", "`", ";", "@", null};
     
     // internal variable to store input string
     private String urlString = new String(); 
                                    
     // gets the starting index of a url or return 0
     private int getStartIdx(String inData) 
     {
         int startIdx = inData.indexOf("<a href=");
         int startIdxhttp = inData.indexOf("http://");
         if (startIdx != -1) {
             if ((startIdxhttp != -1) && (startIdxhttp < startIdx)) {
                 startIdx = startIdxhttp - 7; 
             } else {
                 startIdx = inData.indexOf("</a>");
             }
         } else {
             startIdx = startIdxhttp; 
         }
         if (startIdx < 0) {
             startIdx = 0;
         }
         return startIdx;
     }
     
     // private functino to search a string for a URL http://
     private int searchString(String inputString) 
     {
         StringBuffer outputString = new StringBuffer(); 
         int endIdx = inputString.length();
         int startIdx = getStartIdx(inputString);
         for (int l = startIdx; l<inputString.length()-7; l++) {
             if (inputString.length() > 7) { 
                 // it's a url if :// exists in the string
                 if ( inputString.indexOf("://") != -1 ) {
                     int j = 0; 
                     while (URLString.urlEscCodes[j] != null) {
                         int xidx = inputString.indexOf(URLString.urlEscCodes[j], l); 
                         if (xidx != -1) {
                            if (endIdx > xidx) { 
                                endIdx = xidx;
                            }
                         } 
                         j++;
                     }
                     if (endIdx >= 2) {
                        int tidx = inputString.indexOf(".", endIdx-2);
                        if ((tidx != -1) && (tidx == (endIdx-1))) {
                            endIdx = tidx;
                        } 
                     }
                     if (l>0)  {
                         outputString.append(inputString.substring(0,l));
                     }
                     if ((l < endIdx) && (endIdx > 0)) { 
                         String url = "<a href=\"" + inputString.substring(l,endIdx) + "\">" + inputString.substring(l,endIdx) + "</a>";
                         outputString.append(url);
                     }
                     urlString = new String(outputString.toString());
                     return endIdx;      
                 }
             }
         }
         urlString = new String(inputString);
         return inputString.length();
     }
     
     public String StringSearchURL(String inputString) 
     {
         StringBuffer outputString = new StringBuffer(); 
         int index = 0; 
         int len = inputString.length();
         while (len > index) {
           index += searchString(inputString.substring(index, len));
           outputString.append(urlString);  
         }
         if (outputString.toString().length() > 0) {
             return outputString.toString();
         }
         return inputString; 
     }
}
