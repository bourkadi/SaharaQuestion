<?php

function cron_cache_settings_form($form, &$form_state) {

  $core = array('cache', 'cache_path', 'cache_filter', 'cache_form', 'cache_menu', 'cache_page');
  $cache_tables = array_merge(module_invoke_all('flush_caches'), $core);
  asort($cache_tables);

  $defaults = variable_get('cron_cache_settings', array());
  $form['cron_cache_settings']['#tree'] = TRUE;

  foreach ($cache_tables as $k => $v) {
    $form['cron_cache_settings'][$v]['#tree'] = TRUE;
    $form['cron_cache_settings'][$v][24] = array(
      '#type'  => 'checkbox',
      '#default_value' => (isset($defaults[$v][24]) && $defaults[$v][24]) ? TRUE : FALSE,
    );
    $form['cron_cache_settings'][$v][36] = array(
      '#type'  => 'checkbox',
      '#default_value' => (isset($defaults[$v][36]) && $defaults[$v][36]) ? TRUE : FALSE,
    );
    $form['cron_cache_settings'][$v][48] = array(
      '#type'  => 'checkbox',
      '#default_value' => (isset($defaults[$v][48]) && $defaults[$v][48]) ? TRUE : FALSE,
    );
    $form['cron_cache_settings'][$v][72] = array(
      '#type'  => 'checkbox',
      '#default_value' => (isset($defaults[$v][72]) && $defaults[$v][72]) ? TRUE : FALSE,
    );
  }
  $form['#theme'] = 'cron_cache_settings_form';

  return system_settings_form($form);
}

function theme_cron_cache_settings_form($vars) {
  $form = $vars['form'];

  $header = array(
    '',
    t('24 Hours'),
    t('36 Hours'),
    t('48 Hours'),
    t('72 Hours'),
  );

  $fields = $form['cron_cache_settings'];
  unset($fields['#tree'], $fields['#parents'], $fields['#array_parents'], $fields['#weight'], $fields['#processed'], $fields['#required'],
        $fields['#attributes'], $fields['#title_display'], $fields['#id'], $fields['#sorted']);

  $rows = array();
  foreach ($form['cron_cache_settings'] as $k => $v) {
    $row = array();
    if (isset($fields[$k])) {
      $row[] = $k;
      $row[] = drupal_render($form['cron_cache_settings'][$k][24]);
      $row[] = drupal_render($form['cron_cache_settings'][$k][36]);
      $row[] = drupal_render($form['cron_cache_settings'][$k][48]);
      $row[] = drupal_render($form['cron_cache_settings'][$k][72]);

      $rows[] = $row;
    }
  }

  $table = array(
    'header' => $header,
    'rows' => $rows,
    'attributes' => array(),
    'caption' => '',
    'colgroups' => array(),
    'sticky' => TRUE,
    'empty' => t('There are no caches to configure.'));

  $output  = '<p>'. t('Using the form below, configure when to clear specific caches.') .'</p>';
  $output .= '<p><strong>'. t('Warning:') .'</strong> '. t('Clearing cache_form can break active forms.') .'</p>';

  $output .= theme_table($table);

  return $output . drupal_render_children($form);

}
