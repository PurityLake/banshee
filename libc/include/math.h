/* Copyright 2023 Robert O'Shea
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __H_BANSHEE_MATH__
#define __H_BANSHEE_MATH__

#ifdef __cplusplus
extern "C"
{
#endif

  double fmod(double x, double y);
  float fmodf(float x, float y);

  int isnan(double x);
  int isnanf(float x);

  int isinf(double x);
  int isinff(float x);

#ifdef __cplusplus
}
#endif

#endif /* __H_BANSHEE_MATH__ */
