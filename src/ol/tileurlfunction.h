/**
 * @module ol/tileurlfunction
 */
import {assert} from './asserts.js';
import {modulo} from './math.js';
import {hash as tileCoordHash} from './tilecoord.js';


/**
 * @param {string} template Template.
 * @param {module:ol/tilegrid/TileGrid} tileGrid Tile grid.
 * @return {module:ol/Tile~UrlFunction} Tile URL function.
 */
export function createFromTemplate(template, tileGrid) {
  const zRegEx = /\{z\}/g;
  const xRegEx = /\{x\}/g;
  const yRegEx = /\{y\}/g;
  const dashYRegEx = /\{-y\}/g;
  return (
    /**
     * @param {module:ol/tilecoord~TileCoord} tileCoord Tile Coordinate.
     * @param {number} pixelRatio Pixel ratio.
     * @param {module:ol/proj/Projection} projection Projection.
     * @return {string|undefined} Tile URL.
     */
    function(tileCoord, pixelRatio, projection) {
      if (!tileCoord) {
        return undefined;
      } else {
        return template.replace(zRegEx, tileCoord[0].toString())
          .replace(xRegEx, tileCoord[1].toString())
          .replace(yRegEx, function() {
            const y = -tileCoord[2] - 1;
            return y.toString();
          })
          .replace(dashYRegEx, function() {
            const z = tileCoord[0];
            const range = tileGrid.getFullTileRange(z);
            assert(range, 55); // The {-y} placeholder requires a tile grid with extent
            const y = range.getHeight() + tileCoord[2];
            return y.toString();
          });
      }
    }
  );
}


/**
 * @param {Array.<string>} templates Templates.
 * @param {module:ol/tilegrid/TileGrid} tileGrid Tile grid.
 * @return {module:ol/Tile~UrlFunction} Tile URL function.
 */
export function createFromTemplates(templates, tileGrid) {
  const len = templates.length;
  const tileUrlFunctions = new Array(len);
  for (let i = 0; i < len; ++i) {
    tileUrlFunctions[i] = createFromTemplate(templates[i], tileGrid);
  }
  return createFromTileUrlFunctions(tileUrlFunctions);
}


/**
 * @param {Array.<module:ol/Tile~UrlFunction>} tileUrlFunctions Tile URL Functions.
 * @return {module:ol/Tile~UrlFunction} Tile URL function.
 */
export function createFromTileUrlFunctions(tileUrlFunctions) {
  if (tileUrlFunctions.length === 1) {
    return tileUrlFunctions[0];
  }
  return (
    /**
     * @param {module:ol/tilecoord~TileCoord} tileCoord Tile Coordinate.
     * @param {number} pixelRatio Pixel ratio.
     * @param {module:ol/proj/Projection} projection Projection.
     * @return {string|undefined} Tile URL.
     */
    function(tileCoord, pixelRatio, projection) {
      if (!tileCoord) {
        return undefined;
      } else {
        const h = tileCoordHash(tileCoord);
        const index = modulo(h, tileUrlFunctions.length);
        return tileUrlFunctions[index](tileCoord, pixelRatio, projection);
      }
    }
  );
}


/**
 * @param {module:ol/tilecoord~TileCoord} tileCoord Tile coordinate.
 * @param {number} pixelRatio Pixel ratio.
 * @param {module:ol/proj/Projection} projection Projection.
 * @return {string|undefined} Tile URL.
 */
export function nullTileUrlFunction(tileCoord, pixelRatio, projection) {
  return undefined;
}


/**
 * @param {string} url URL.
 * @return {Array.<string>} Array of urls.
 */
export function expandUrl(url) {
  const urls = [];
  let match = /\{([a-z])-([a-z])\}/.exec(url);
  if (match) {
    // char range
    const startCharCode = match[1].charCodeAt(0);
    const stopCharCode = match[2].charCodeAt(0);
    let charCode;
    for (charCode = startCharCode; charCode <= stopCharCode; ++charCode) {
      urls.push(url.replace(match[0], String.fromCharCode(charCode)));
    }
    return urls;
  }
  match = match = /\{(\d+)-(\d+)\}/.exec(url);
  if (match) {
    // number range
    const stop = parseInt(match[2], 10);
    for (let i = parseInt(match[1], 10); i <= stop; i++) {
      urls.push(url.replace(match[0], i.toString()));
    }
    return urls;
  }
  urls.push(url);
  return urls;
}
