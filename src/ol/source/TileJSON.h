/**
 * @module ol/source/TileJSON
 */
// FIXME check order of async callbacks

/**
 * @see http://mapbox.com/developers/api/
 */

import {inherits} from '../util.js';
import {createFromTemplates} from '../tileurlfunction.js';
import {assert} from '../asserts.js';
import {applyTransform, intersects} from '../extent.js';
import {jsonp as requestJSONP} from '../net.js';
import {get as getProjection, getTransformFromProjections} from '../proj.js';
import SourceState from '../source/State.js';
import TileImage from '../source/TileImage.js';
import {createXYZ, extentFromProjection} from '../tilegrid.js';

/**
 * @typedef {Object} Options
 * @property {module:ol/source/Source~AttributionLike} [attributions] Attributions.
 * @property {number} [cacheSize=2048] Cache size.
 * @property {null|string} [crossOrigin] The `crossOrigin` attribute for loaded images.  Note that
 * you must provide a `crossOrigin` value if you are using the WebGL renderer or if you want to
 * access pixel data with the Canvas renderer.  See
 * {@link https://developer.mozilla.org/en-US/docs/Web/HTML/CORS_enabled_image} for more detail.
 * @property {boolean} [jsonp=false] Use JSONP with callback to load the TileJSON.
 * Useful when the server does not support CORS..
 * @property {boolean} [reprojectionErrorThreshold=0.5] Maximum allowed reprojection error (in pixels).
 * Higher values can increase reprojection performance, but decrease precision.
 * @property {tileJSON} [tileJSON] TileJSON configuration for this source.
 * If not provided, `url` must be configured.
 * @property {module:ol/Tile~LoadFunction} [tileLoadFunction] Optional function to load a tile given a URL. The default is
 * ```js
 * function(imageTile, src) {
 *   imageTile.getImage().src = src;
 * };
 * ```
 * @property {string} [url] URL to the TileJSON file. If not provided, `tileJSON` must be configured.
 * @property {boolean} [wrapX=true] Whether to wrap the world horizontally.
 * @property {number} [transition] Duration of the opacity transition for rendering.
 * To disable the opacity transition, pass `transition: 0`.
 */


/**
 * @classdesc
 * Layer source for tile data in TileJSON format.
 *
 * @constructor
 * @extends {module:ol/source/TileImage}
 * @param {module:ol/source/TileJSON~Options=} options TileJSON options.
 * @api
 */
const TileJSON = function(options) {

  /**
   * @type {TileJSON}
   * @private
   */
  this.tileJSON_ = null;

  TileImage.call(this, {
    attributions: options.attributions,
    cacheSize: options.cacheSize,
    crossOrigin: options.crossOrigin,
    projection: getProjection('EPSG:3857'),
    reprojectionErrorThreshold: options.reprojectionErrorThreshold,
    state: SourceState.LOADING,
    tileLoadFunction: options.tileLoadFunction,
    wrapX: options.wrapX !== undefined ? options.wrapX : true,
    transition: options.transition
  });

  if (options.url) {
    if (options.jsonp) {
      requestJSONP(options.url, this.handleTileJSONResponse.bind(this),
        this.handleTileJSONError.bind(this));
    } else {
      const client = new XMLHttpRequest();
      client.addEventListener('load', this.onXHRLoad_.bind(this));
      client.addEventListener('error', this.onXHRError_.bind(this));
      client.open('GET', options.url);
      client.send();
    }
  } else if (options.tileJSON) {
    this.handleTileJSONResponse(options.tileJSON);
  } else {
    assert(false, 51); // Either `url` or `tileJSON` options must be provided
  }

};

inherits(TileJSON, TileImage);


/**
 * @private
 * @param {Event} event The load event.
 */
TileJSON.prototype.onXHRLoad_ = function(event) {
  const client = /** @type {XMLHttpRequest} */ (event.target);
  // status will be 0 for file:// urls
  if (!client.status || client.status >= 200 && client.status < 300) {
    let response;
    try {
      response = /** @type {TileJSON} */(JSON.parse(client.responseText));
    } catch (err) {
      this.handleTileJSONError();
      return;
    }
    this.handleTileJSONResponse(response);
  } else {
    this.handleTileJSONError();
  }
};


/**
 * @private
 * @param {Event} event The error event.
 */
TileJSON.prototype.onXHRError_ = function(event) {
  this.handleTileJSONError();
};


/**
 * @return {TileJSON} The tilejson object.
 * @api
 */
TileJSON.prototype.getTileJSON = function() {
  return this.tileJSON_;
};


/**
 * @protected
 * @param {TileJSON} tileJSON Tile JSON.
 */
TileJSON.prototype.handleTileJSONResponse = function(tileJSON) {

  const epsg4326Projection = getProjection('EPSG:4326');

  const sourceProjection = this.getProjection();
  let extent;
  if (tileJSON.bounds !== undefined) {
    const transform = getTransformFromProjections(
      epsg4326Projection, sourceProjection);
    extent = applyTransform(tileJSON.bounds, transform);
  }

  const minZoom = tileJSON.minzoom || 0;
  const maxZoom = tileJSON.maxzoom || 22;
  const tileGrid = createXYZ({
    extent: extentFromProjection(sourceProjection),
    maxZoom: maxZoom,
    minZoom: minZoom
  });
  this.tileGrid = tileGrid;

  this.tileUrlFunction = createFromTemplates(tileJSON.tiles, tileGrid);

  if (tileJSON.attribution !== undefined && !this.getAttributions()) {
    const attributionExtent = extent !== undefined ?
      extent : epsg4326Projection.getExtent();

    this.setAttributions(function(frameState) {
      if (intersects(attributionExtent, frameState.extent)) {
        return [tileJSON.attribution];
      }
      return null;
    });

  }
  this.tileJSON_ = tileJSON;
  this.setState(SourceState.READY);

};


/**
 * @protected
 */
TileJSON.prototype.handleTileJSONError = function() {
  this.setState(SourceState.ERROR);
};
export default TileJSON;
