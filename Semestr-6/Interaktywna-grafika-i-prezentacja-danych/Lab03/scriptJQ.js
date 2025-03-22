$( function() {
    $( "#accordion" ).accordion({
      animate: 1000,
      header: "> div > h3",
      heightStyle: "content"
    }).sortable({
      axis: "y",
      handle: "h3",
      stop: function( event, ui ) {
        // IE doesn't register the blur when sorting
        // so trigger focusout handlers to remove .ui-state-focus
        ui.item.children( "h3" ).triggerHandler( "focusout" );

        // Refresh accordion to handle new order
        $( this ).accordion( "refresh" );
      }
    });
  } );

  $( function() {
    $( "input" ).checkboxradio();
  } );

  $(function(){

    $('#checkbox-1').click(function() {
        $( "#users" ).toggleClass( "newColor", 400 );
    });
  });


$( function() {
$( "#tabs" ).tabs();
var previouslyFocused = false;
 
    tabs.find( ".ui-tabs-nav" ).sortable({
      axis: "x",
 
      // Sortable removes focus, so we need to restore it if the tab was focused
      // prior to sorting
      start: function(event, ui) {
        previouslyFocused = document.activeElement === ui.item[ 0 ];
      },
      stop: function(event, ui) {
        tabs.tabs( "refresh" );
        if (previouslyFocused) {
          ui.item.trigger( "focus" );
        }
      }
    });
} );

$( "#radio" ).controlgroup();



$( function() {
    var dialog, form,
 
      // From https://html.spec.whatwg.org/multipage/input.html#e-mail-state-%28type=email%29
      name = $( "#name" ),
      email = $( "#email" ),
      password = $( "#password" ),
      allFields = $( [] ).add( name ).add( email ).add( password ),
      tips = $( ".validateTips" );
 
    function updateTips( t ) {
      tips
        .text( t )
        .addClass( "ui-state-highlight" );
      setTimeout(function() {
        tips.removeClass( "ui-state-highlight", 1500 );
      }, 500 );
    }
 
    function checkLength( o, n, min, max ) {
      if ( o.val().length > max || o.val().length < min ) {
        o.addClass( "ui-state-error" );
        updateTips( "Length of " + n + " must be between " +
          min + " and " + max + "." );
        return false;
      } else {
        return true;
      }
    }
 
    function checkRegexp( o, regexp, n ) {
      if ( !( regexp.test( o.val() ) ) ) {
        o.addClass( "ui-state-error" );
        updateTips( n );
        return false;
      } else {
        return true;
      }
    }
 
    function addUser() {
      var valid = true;
      allFields.removeClass( "ui-state-error" );
 
      valid = valid && checkLength( name, "imie", 3, 16 );
      valid = valid && checkLength( email, "nazwisko", 3, 80 );
      valid = valid && checkLength( password, "punkty", 1, 10 );
 
      if ( valid ) {
        $( "#users tbody" ).append( "<tr>" +
          "<td>" + name.val() + "</td>" +
          "<td>" + email.val() + "</td>" +
          "<td>" + password.val() + "</td>" +
        "</tr>" );
        dialog.dialog( "close" );
      }
      return valid;
    }
 
    dialog = $( "#dialog-form" ).dialog({
      autoOpen: false,
      height: 500,
      width: 400,
      modal: true,
      buttons: {
        "Dodaj ": addUser,
        Anuluj: function() {
          dialog.dialog( "close" );
        }
      },
      close: function() {
        form[ 0 ].reset();
        allFields.removeClass( "ui-state-error" );
      }
    });
 
    form = dialog.find( "form" ).on( "submit", function( event ) {
      event.preventDefault();
      addUser();
    });
 
    $( "#create-user" ).button().on( "click", function() {
      dialog.dialog( "open" );
    });
  } );
  

  
	$(function() {
		$( "#dialog-form" ).dialog({
			autoOpen: false,
			show: {
				effect: "blind",
				duration: 1500
			},
			hide: {
				effect: "clip",
				duration: 1000
			}
		});

		$( "#create-user" ).click(function() {
			$( "#dialog" ).dialog( "open" );
		});
	});
	

  $( function() {
    $( "#temp" ).each(function() {
      var value = parseInt( $( this ).text(), 10 );
      $( this ).empty().slider({
        value: value,
        range: "min",
        min: 15,
        max: 30,
        animate: true,
        orientation: "vertical"
      });
    });

    $( "#humi" ).each(function() {
      var value = parseInt( $( this ).text(), 10 );
      $( this ).empty().slider({
        value: value,
        range: "min",
        min: 0,
        max: 100,
        animate: true,
        orientation: "vertical"
      });
    });

    $( "#AQ" ).each(function() {
      var value = parseInt( $( this ).text(), 10 );
      $( this ).empty().slider({
        value: value,
        range: "min",
        min: 0,
        max: 500,
        animate: true,
        orientation: "vertical"
      });
    });
  } );

  function getValueTemp(){
    var value = $( "#temp" ).slider( "option", "value" );
    //var colVal = "#" + value + value + value;
    //console.log(colVal);

    //$(".ui-slider-range-min").css("background-color", colVal);
  }

  

  $(document).ready(function() {
    $("#temperature-slider").slider({
      min: 15,
      max: 25,
      value: 20,
      slide: function(event, ui) {
        $("#temperature-value").text(ui.value + "°C");
        var color = getColorTemperature(ui.value);
        $(this).css("background", color);
      }
    });

    $("#humidity-slider").slider({
      min: 0,
      max: 100,
      value: 50,
      slide: function(event, ui) {
        $("#humidity-value").text(ui.value + "%");
        var color = getColorHumidity(ui.value);
        $(this).css("background", color);
      }
    });

    $("#airquality-slider").slider({
      min: 0,
      max: 500,
      value: 250,
      slide: function(event, ui) {
        $("#airquality-value").text(ui.value);
        var color = getColorAirQuality(ui.value);
        $(this).css("background", color);
      }
    });

    function getColorTemperature(value) {
      var r = Math.min(255, (value - 15) * 20);
      var b = Math.min(255, (25 - value) * 20);
      return "rgb(" + r + ", 20, " + b + ")";
    }

    function getColorHumidity(value) {
      var g = Math.min(255, (value + 125));
      return "rgb(100, 100," + g + ")";
    }

    function getColorAirQuality(value) {
      var red = Math.min(255, value * 0.51);
      var green = Math.max(0, 255 - value * 0.51);
      return "rgb(" + red + ", " + green + ", 0)";
    }
  });

  $( function() {
    var tabTitle = $( "#tab_title" ),
      tabContent = $( "#tab_content" ),
      tabTemplate = "<li><a href='#{href}'>#{label}</a> <span class='ui-icon ui-icon-close' role='presentation'>Remove Tab</span></li>",
      tabCounter = 3;
 
    var tabs = $( "#tabs" ).tabs();
 
    // Modal dialog init: custom buttons and a "close" callback resetting the form inside
    var dialog = $( "#dialog" ).dialog({
      autoOpen: false,
      modal: true,
      buttons: {
        Add: function() {
          addTab();
          $( this ).dialog( "close" );
        },
        Cancel: function() {
          $( this ).dialog( "close" );
        }
      },
      close: function() {
        form[ 0 ].reset();
      }
    });
 
    // AddTab form: calls addTab function on submit and closes the dialog
    var form = dialog.find( "form" ).on( "submit", function( event ) {
      addTab();
      dialog.dialog( "close" );
      event.preventDefault();
    });
 
    // Actual addTab function: adds new tab using the input from the form above
    function addTab() {
      var label = tabTitle.val() || "Tab " + tabCounter,
        id = "tabs-" + tabCounter,
        li = $( tabTemplate.replace( /#\{href\}/g, "#" + id ).replace( /#\{label\}/g, label ) ),
        tabContentHtml = tabContent.val() || "Tab " + tabCounter + " content.";
 
      tabs.find( ".ui-tabs-nav" ).append( li );
      tabs.append( "<div id='" + id + "'><p>" + tabContentHtml + "</p></div>" );
      tabs.tabs( "refresh" );
      tabCounter++;
    }
 
    // AddTab button: just opens the dialog
    $( "#add_tab" )
      .button()
      .on( "click", function() {
        dialog.dialog( "open" );
      });
 
    // Close icon: removing the tab on click
    tabs.on( "click", "span.ui-icon-close", function() {
      var panelId = $( this ).closest( "li" ).remove().attr( "aria-controls" );
      $( "#" + panelId ).remove();
      tabs.tabs( "refresh" );
    });
 
    tabs.on( "keyup", function( event ) {
      if ( event.altKey && event.keyCode === $.ui.keyCode.BACKSPACE ) {
        var panelId = tabs.find( ".ui-tabs-active" ).remove().attr( "aria-controls" );
        $( "#" + panelId ).remove();
        tabs.tabs( "refresh" );
      }
    });
  } );