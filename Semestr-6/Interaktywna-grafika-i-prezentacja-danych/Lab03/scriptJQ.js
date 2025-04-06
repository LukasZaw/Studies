$(function () {
  $("#accordion").accordion({
    animate: {
      duration: 2000,
      easing: "easeOutBounce",
    },
  });
});

$(function () {
  $("#tabs")
    .tabs({
      show: { effect: "fadeIn", duration: 500 },
    })
    .find(".ui-tabs-nav")
    .sortable({
      axis: "x",
      stop: function () {
        $("#tabs").tabs("refresh");
      },
    });

  var tabCounter = 3; // Start after existing tabs
  var dialog, form;

  function addTab() {
    var tabTitle = $("#tab-title").val();
    var tabContent = $("#tab-content").val();

    if (tabTitle && tabContent) {
      var id = "tabs-" + ++tabCounter;
      $("#tabs ul").append(
        "<li><a href='#" + id + "'>" + tabTitle + "</a></li>"
      );
      $("#tabs").append("<div id='" + id + "'><p>" + tabContent + "</p></div>");
      $("#tabs").tabs("refresh");
      dialog.dialog("close");
    }
  }

  dialog = $("#add-tab-dialog").dialog({
    autoOpen: false,
    modal: true,
    buttons: {
      "Dodaj zakładkę": addTab,
      Anuluj: function () {
        dialog.dialog("close");
      },
    },
    close: function () {
      form[0].reset();
    },
  });

  form = dialog.find("form").on("submit", function (event) {
    event.preventDefault();
    addTab();
  });

  $("#add-tab-button")
    .button()
    .on("click", function () {
      dialog.dialog("open");
    });
});

$("#radio").controlgroup();

$(function () {
  // Dodanie checkboxa do nagłówka tabeli
  $("#users").before(
    '<div><label><input type="checkbox" id="toggle-color"> Zaznacz parzyste wiersze</label></div>'
  );

  // Obsługa zdarzenia kliknięcia checkboxa
  $("#toggle-color").on("change", function () {
    $("#users tr:even").each(function () {
      $(this).toggleClass("highlight", 500);
    });
  });
});

$(function () {
  var dialog,
    form,
    // From https://html.spec.whatwg.org/multipage/input.html#e-mail-state-%28type=email%29
    name = $("#name"),
    email = $("#email"),
    password = $("#password"),
    allFields = $([]).add(name).add(email).add(password),
    tips = $(".validateTips");

  function updateTips(t) {
    tips.text(t).addClass("ui-state-highlight");
    setTimeout(function () {
      tips.removeClass("ui-state-highlight", 1500);
    }, 500);
  }

  function checkLength(o, n, min, max) {
    if (o.val().length > max || o.val().length < min) {
      o.addClass("ui-state-error");
      updateTips(
        "Length of " + n + " must be between " + min + " and " + max + "."
      );
      return false;
    } else {
      return true;
    }
  }

  function checkRegexp(o, regexp, n) {
    if (!regexp.test(o.val())) {
      o.addClass("ui-state-error");
      updateTips(n);
      return false;
    } else {
      return true;
    }
  }

  function addUser() {
    var valid = true;
    allFields.removeClass("ui-state-error");

    valid = valid && checkLength(name, "imie", 3, 16);
    valid = valid && checkLength(email, "nazwisko", 3, 80);
    valid = valid && checkLength(password, "punkty", 1, 10);

    if (valid) {
      var newRow = $(
        "<tr style='display: none;'>" +
          "<td>" +
          name.val() +
          "</td>" +
          "<td>" +
          email.val() +
          "</td>" +
          "<td>" +
          password.val() +
          "</td>" +
          "<td><button class='delete-row'>Usuń</button></td>" +
          "</tr>"
      );
      $("#users tbody").append(newRow);
      newRow.show("slow"); // Smoothly show the new row
      dialog.dialog("close");
    }
    return valid;
  }

  $(document).on("click", ".delete-row", function () {
    $(this)
      .closest("tr")
      .hide("slow", function () {
        $(this).remove();
      });
  });

  dialog = $("#dialog-form").dialog({
    autoOpen: false,
    height: 500,
    width: 400,
    modal: true,
    buttons: {
      "Dodaj ": addUser,
      Anuluj: function () {
        dialog.dialog("close");
      },
    },
    close: function () {
      form[0].reset();
      allFields.removeClass("ui-state-error");
    },
  });

  form = dialog.find("form").on("submit", function (event) {
    event.preventDefault();
    addUser();
  });

  $("#create-user")
    .button()
    .on("click", function () {
      dialog.dialog("open");
    });
});

$(function () {
  $("#dialog-form").dialog({
    autoOpen: false,
    show: {
      effect: "blind",
      duration: 1500,
    },
    hide: {
      effect: "clip",
      duration: 1000,
    },
  });

  $("#create-user").click(function () {
    $("#dialog").dialog("open");
  });
});

$(function () {
  $("#temp").each(function () {
    var value = parseInt($(this).text(), 10);
    $(this).empty().slider({
      value: value,
      range: "min",
      min: 15,
      max: 30,
      animate: true,
      orientation: "vertical",
    });
  });

  $("#humi").each(function () {
    var value = parseInt($(this).text(), 10);
    $(this).empty().slider({
      value: value,
      range: "min",
      min: 0,
      max: 100,
      animate: true,
      orientation: "vertical",
    });
  });

  $("#AQ").each(function () {
    var value = parseInt($(this).text(), 10);
    $(this).empty().slider({
      value: value,
      range: "min",
      min: 0,
      max: 500,
      animate: true,
      orientation: "vertical",
    });
  });
});

function getValueTemp() {
  var value = $("#temp").slider("option", "value");
  //var colVal = "#" + value + value + value;
  //console.log(colVal);

  //$(".ui-slider-range-min").css("background-color", colVal);
}

$(document).ready(function () {
  $("#temperature-slider").slider({
    min: 15,
    max: 25,
    value: 20,
    slide: function (event, ui) {
      $("#temperature-value").text(ui.value + "°C");
      var color = getColorTemperature(ui.value);
      $(this).css("background", color);
    },
  });

  $("#humidity-slider").slider({
    min: 0,
    max: 100,
    value: 50,
    slide: function (event, ui) {
      $("#humidity-value").text(ui.value + "%");
      var color = getColorHumidity(ui.value);
      $(this).css("background", color);
    },
  });

  $("#airquality-slider").slider({
    min: 0,
    max: 500,
    value: 250,
    slide: function (event, ui) {
      $("#airquality-value").text(ui.value);
      var color = getColorAirQuality(ui.value);
      $(this).css("background", color);
    },
  });

  function getColorTemperature(value) {
    var r = Math.min(255, (value - 15) * 20);
    var b = Math.min(255, (25 - value) * 20);
    return "rgb(" + r + ", 20, " + b + ")";
  }

  function getColorHumidity(value) {
    var g = Math.min(255, value + 125);
    return "rgb(100, 100," + g + ")";
  }

  function getColorAirQuality(value) {
    var red = Math.min(255, value * 0.51);
    var green = Math.max(0, 255 - value * 0.51);
    return "rgb(" + red + ", " + green + ", 0)";
  }
});

$(function () {
  // Initialize the calendar
  $("#calendar").datepicker();

  // Cycler functionality
  function cycleImages() {
    var $active = $("#cycler img:visible");
    var $next = $active.next().length ? $active.next() : $("#cycler img:first");
    $active.fadeOut(2000, function () {
      $next.fadeIn(2000);
    });
  }
  setInterval(cycleImages, 4000);
});
