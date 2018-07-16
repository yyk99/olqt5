#include <gtest/gtest.h>

//import Feature from '../../../src/ol/Feature.js';
#include "../../../src/ol/Feature.h"
//import {defaultLoadFunction} from '../../../src/ol/VectorImageTile.js';
#include "../../../src/ol/VectorImageTile.h"
//import VectorTile from '../../../src/ol/VectorTile.js';
#include "../../../src/ol/VectorTile.h"
//import {listen} from '../../../src/ol/events.js';
#include "../../../src/ol/events.h"
//import TextFeature from '../../../src/ol/format/TextFeature.js';
#include "../../../src/ol/format/TextFeature.h"
//import {get as getProjection} from '../../../src/ol/proj.js';
#include "../../../src/ol/proj.h"
//import Projection from '../../../src/ol/proj/Projection.js';
#include "../../../src/ol/proj/Projection.h"

using namespace ol;

//
//
TEST(ol_VectorTile, t1)
{
    //describe('ol.VectorTile', function() {
    //
    //  it('loader sets features on the tile and updates proj units', function(done) {
    //    // mock format that return a tile-pixels feature
    auto format = ol::format::TextFeature();
    //    format.readProjection = function(source) {
    //      return new Projection({
    //        code: '',
    //        units: 'tile-pixels'
    //      });
    //    };
    //    format.readFeatures = function(source, options) {
    //      return [new Feature()];
    //    };
    //
    //    const tile = new VectorTile([0, 0, 0], null, null, format);
    auto tile = VectorTile(ol::tilecoord::TileCoord({ 0, 0, 0 }), 0, std::string(), format, /*opt*/ 0, 0);
    std::string url = "spec/ol/data/point.json";
    //
    //    defaultLoadFunction(tile, url);
    //    const loader = tile.loader_;
    //    listen(tile, 'change', function(e) {
    //      expect(tile.getFeatures().length).to.be.greaterThan(0);
    //      expect(tile.getProjection().getUnits()).to.be('tile-pixels');
    //      done();
    //    });
    //    loader.call(tile, [], 1, getProjection('EPSG:3857'));
    //  });
    //
    //});
}
