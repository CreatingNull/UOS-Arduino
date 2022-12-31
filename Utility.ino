/*
 *	UOS Arduino Firmware
 *	See <https://wiki.nulltek.xyz/projects/uos/>
 *
 *	Copyright © 2023 Steve Richardson (Creating Null)
 *	See LICENSE.md
 *	<https://github.com/CreatingNull/UOS-Arduino/>
 *
 *	Helper algorithms and functions
 */

// Binary search to locate the index of a value if it exists in a sorted array.
// 255 if not found.
uint8_t find_in_sorted_array(uint8_t value, const uint8_t arr[],
                             uint8_t arr_len) {
  uint8_t low_range = 0;
  uint8_t high_range = arr_len - 1;
  uint8_t index = uint8_t(high_range / 2);  // start in the middle
  for (uint8_t i = 0; i < arr_len; i++) {
    if (arr[index] == value) {
      return index;
    } else if (value < arr[index]) {
      high_range = index - 1;
    } else {
      low_range = index + 1;
    }
    uint8_t index_prior = index;
    index = uint8_t((high_range + low_range) / 2);
    if (index_prior == index) {
      return 255;  // Value doesn't exist
    }
  }
  return 255;
}
