var ss = SpreadsheetApp.openById('1gcYI826jGG-C5fFl9iq1LBvpnGVTxCuk17LkRd-YYQg');

function doGet(e) {
  if("post" in e.parameter){
    var content = e.parameter.post;
    if (content != undefined){
      var sheet = ss.getSheetByName('RECEIVE');

      var time = new Date().toLocaleString();
      var lr = sheet.getLastRow();
      
      sheet.getRange(lr+1,1).setValue(content);
      sheet.getRange(lr+1,2).setValue(time); 
    }
  }
  else{
  var sheet = ss.getSheetByName('SEND');

  content = sheet.getRange('A2:C12').getValues();
  return ContentService.createTextOutput(content);
  }

}

function doPost(e) {
  var content = e.parameter.message;
  if (content != undefined){
    var sheet = ss.getSheetByName('RECEIVE');

    var time = new Date().toLocaleString();
    var lr = sheet.getLastRow();
    
    sheet.getRange(lr+1,1).setValue(content);
    sheet.getRange(lr+1,2).setValue(time); 
  }  
}
