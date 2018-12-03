(function ($) {
  Drupal.behaviors.view_mode_modal = {
    attach: function (context) {
      //
    }
  };
  
  /**
   * Provide the HTML to create the modal dialog.
   */
  Drupal.theme.prototype.ViewModeModal = function () {
    var html = ''
    html += '  <div id="ctools-modal">'
    html += '    <div class="ctools-modal-content ' + Drupal.CTools.Modal.currentSettings.htmlClass + '">'
    html += '      <div class="modal-header">';
    html += '        <a class="close" href="#">&times;</a>';
    html += '        <h3 id="modal-title" class="modal-title">&nbsp;</h3>';
    html += '      </div>';
    html += '      <div id="modal-content" class="modal-content">';
    html += '      </div>';
    html += '    </div>';
    html += '  </div>';

    return html;
  }
  
})(jQuery);
