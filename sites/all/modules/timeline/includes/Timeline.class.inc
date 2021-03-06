<?php

/**
 * @file
 * Class Timeline
 */

/**
 *   id - the XHTML identifier of the timeline element
 *   orientation - HORIZONTAL or VERTICAL
 *   incial_focus - the initial focus date of the timeline
 *   timezone - the timezone represented by # of hours difference from GMT
 *   controls - whether to show the filtering controls
 *   bands - interval settings of the bands
 *   summary - interval settings of the summary band
 *   timeline_start - A date to limit the beginning of the timeline.
 *   timeline_end - A date to limit the end of the timeline.
 *   theme_name - for the use of several themes
 *   bubble_max_height - A maximal height for bubbles (A scrollbar would be added on taller bubbles)
 *   bubble_width - Width of the bubbles
 */
class Timeline {

  var $view;
  var $data;
  var $events;
  var $sets;
  var $dateformat;
  var $color_id = 0;

  /**
   * Constructor.
   *
   * @param $view
   */
  function __construct(&$view, $sets) {
    $this->view = $view;
    $this->sets = $sets;
    $this->dateformat = 'iso8601';

    $this->data['events'] = $this->getEvents();
    $this->data['id'] = $this->view->name;
    $this->data['orientation'] = 0;
    $this->data['initial_focus'] = $this->getDefinedDateField($view->style_options['bands']['focus'], $view->style_options['bands']['focus_custom']);
    $this->data['timezone'] = 0; // missing
    $this->data['controls'] = FALSE; // missing
    $this->data['bands'] = $this->getBands();
    $this->data['summary'] = drupal_strtoupper($view->style_options['bands']['band2_unit']);
    $this->data['band1_unit_width'] = $view->style_options['bands']['band1_unit_width'];
    $this->data['band2_unit_width'] = $view->style_options['bands']['band2_unit_width'];

    // startsOn ?!? ether.js on line 22 -fd
    //$this->data['timeline_start'] = $this->get_defined_date_field($view->style_options['limit']['start'], $view->style_options['limit']['custom_start']);
    //$this->data['timeline_end'] = $this->get_defined_date_field($view->style_options['limit']['end'], $view->style_options['limit']['custom_end']);
    $this->data['theme'] = $view->style_options['display']['appearance']['theme'];
    $this->data['bubble_max_height'] = $view->style_options['display']['appearance']['bubble_height'];
    $this->data['bubble_width'] = $view->style_options['display']['appearance']['bubble_width'];
  }

  function timeline_to_json() {
    drupal_add_js(array('timeline' => array($this->data['id'] => $this->data)), 'setting');
  }

  function debug() {
    return $this->data;
  }


  /**
   *
   */
  function getEvents() {

    $events = array();
    if (!empty($this->view->result)) {
      $this->view->row_index = 0;
      foreach ($this->sets as $k => $set) {
        $css_selector = $this->generateCssSelector();
        $color = FALSE;
        if (isset($this->view->style_options['grouping']) && $this->view->style_options['grouping'] != '') {
          $color = $this->getColor();
        }

        foreach ($set as $row_key => $row) {
          $this->view->row_index = $row_key;
          $event = new TimelineEvent($this->view, $row, $this->dateformat, $css_selector, $color);
          if ($event->getData()) {
            $events[] = $event->getData();
          }
        }
      }
    }
    return array(
      'events' => $events,
      'dateTimeFormat' => $this->dateformat,
    );
  }

  function getBands() {
    $bands = array();
    $bands[] = drupal_strtoupper($this->view->style_options['bands']['band1_unit']);
    return $bands;
  }


  /**
   * Get the actual field value based on the timeline views settings and the result set of events.
   *
   * @param
   *   $option - name of the selected option
   *   result - the result set of events
   *
   * @return
   *   formated date
   *
   * Note: -fd
   * First and last fields have to be improved:
   * If the view is not sorted on the start date this would lead wrong dates.
   * Last should also check if the event has an "end" date
   */
  function getDefinedDateField($option, $options_field = '') {
    $timezone = timeline_get_timezone();

    // Make sure that if there is no result that a valid date (today) is getting served.
    if ($option != 'today' && $option != 'custom' && count($this->data['events']['events']) == 0) {
      $option = 'today';
    }
    switch ($option) {
      case 'today':
        return timeline_convert_to_gregorian(REQUEST_TIME, 'timestamp', $timezone, $timezone);
      case 'first':
        return timeline_convert_to_gregorian($this->data['events']['events'][0]['start'], 'iso8601', $timezone, $timezone);
      case 'last':
        return timeline_convert_to_gregorian($this->data['events']['events'][count($this->data['events']['events']) - 1]['start'], 'iso8601', $timezone, $timezone);
      case 'middle':
        $end = timeline_convert_to_timestamp($this->data['events']['events'][count($this->data['events']['events']) - 1]['start'], 'iso8601', $timezone, $timezone);
        $start = timeline_convert_to_timestamp($this->data['events']['events'][0]['start'], 'iso8601', $timezone, $timezone);
        $middle = round(($start + $end) / 2, 0);
        return timeline_convert_to_gregorian($middle, 'timestamp', $timezone, $timezone);
      case 'median':
        foreach ($this->data['events']['events'] as $date) {
          $t[] = timeline_convert_to_timestamp($date['start'], 'iso8601', $timezone, $timezone);
        }
        sort($t);
        return timeline_convert_to_gregorian($t[round(count($t)/2)], 'timestamp', $timezone, $timezone);
      case 'custom':
        if ($options_field != '') {
          return timeline_convert_to_gregorian(strtotime($options_field), 'timestamp', $timezone, $timezone);
        }
    }
    return FALSE;
  }

  function getColor() {
    $colors = array(
      '#0A3FAC',
      '#CE1500',
      '#0A8624',
      '#FF6A00',
      '#CE0C72',
      '#F8D100',
    );

    // Override color information if specified
    if (isset($this->view->style_options['colors']['values']) && $this->view->style_options['colors']['values'] != '') {
      $colors = preg_split("/\r\n|\n/", $this->view->style_options['colors']['values']);
    }

    $tmp = $this->color_id;
    $this->color_id++;

    while ($tmp >= count($colors)) {
      $tmp = $tmp - count($colors);
    }
    return $colors[$tmp];
  }

  function generateCssSelector() {
    return $this->view->name . '-set-' . $this->color_id;
  }
}
