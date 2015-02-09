

function test(){                                    //Main function




$.ajax({                                          //Ajax call to databaseresults.xml
    url: 'xml/databaseresults.xml',
    dataType: 'xml',
    success: function(data) {




var min=document.getElementById("min").value;                 //Acquires min range value from html form
var max=document.getElementById("max").value;                 //Acquires max range value from html form



for (i=min; i<=max; i++) {                                    //Iterate over range and display values from XML file

var id=i;


        $(data).find('xml RECORD'+id).each(function() {         //Acquire ID, TIME, MONEY fields from XML file
        var statusid = $(this).find('ID').text();
        var statustime = $(this).find('TIME').text();
        var statusmoney = $(this).find('MONEY').text();


	 
       
        
        $('.databaseresults ul1').append(statusid+"\n");        //Append values and place them under the databaseresults/ul1 NODE
        $('.databaseresults ul1').append(statustime+"\n");
        $('.databaseresults ul1').append(statusmoney+"\n");
        $('.databaseresults ul1').append("<br>");


        
});
}

},
    error: function() {                                           //Error handling
        $('.xml').text('Failed to get feed');
    }
});





}



function refresh(){
document.location.reload();
}
