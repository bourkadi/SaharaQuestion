<?php

/**
 * @file
 * Hooks provided by JW Player.
 */

/**
 * Implements hook_jw_player_plugin_info().
 *
 * @return array Associative array of plugins keyed by actual plugin id
 */
function hook_jw_player_plugin_info($preset) {
  // Create a plugin keyed by its actual plugin id.
  $plugins['foo'] = array(
    'name' => t('Foobar'),
    'description' => t('A plugin to do foobar'),
    // Note: Each option should be in a valid FAPI format, as it is directly
    // referenced in the preset settings form, except the '#title' may be
    // omitted for the name of the option to be taken as default.
    'config options' => array(
      'accountid' => array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#size' => 15,
        '#default_value' => 'bar'
      ),
      'param2' => array(
        '#type' => 'select',
        '#options' => array('TRUE' => 'TRUE', 'FALSE' => 'FALSE'),
        '#default_value' => 'TRUE',
        '#description' => t('Enables the controls on an item when playing')),
    ),
  );
  return $plugins;
}
/**
 * Checks a file for JW Player supported media formats.
 *
 * This hook allow third party module to provide media formats verification for
 * video and audio streams inside a file to be used in JW Player.
 *
 * @param array|object $file
 *   A file object (or array) to check for support.
 *
 * @return bool
 *   TRUE if the file is supported by JW Player.
 */
function hook_jw_player_supports($file) {

}

/**
 * Alter the list of mime types supported by JW Player.
 *
 * @param array $types
 *   A list of mime types as an array of strings.
 */
function hook_jw_player_supported_mimetypes_alter(&$types) {

}