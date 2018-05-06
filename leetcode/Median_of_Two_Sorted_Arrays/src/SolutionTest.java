import static org.junit.Assert.*;

public class SolutionTest {
    private Solution s = new Solution();

    @org.junit.Test
    public void medianOfEmpty() {
        assertEquals(-1.0, Solution.median(new int[]{1, 2, 3}, 1, 1), 0.001);
    }

    @org.junit.Test
    public void medianOfOneElement() {
        assertEquals(3.0, Solution.median(new int[] {1, 2, 3}, 2, 3), 0.001);
    }

    @org.junit.Test
    public void medianOfEvenElements() {
        assertEquals(1.5, Solution.median(new int[] {1, 2, 3, 4}, 0, 2), 0.001);
    }

    @org.junit.Test
    public void medianOfOddElements() {
        assertEquals(3.0, Solution.median(new int[] {1, 2, 3, 4}, 1, 4), 0.001);
    }

    @org.junit.Test
    public void medianEquivalentToTheControlImplementation() {
        int[] xs = new int[] {3, 5, 6, 6, 7, 8};
        assertEquals(Merge.median(xs), Solution.median(xs, 0, xs.length), 0.001);
    }

    @org.junit.Test
    public void bothEmpty() {
        assertEquals(-1.0, s.findMedianSortedArrays(new int[0], new int[0]), 0.001);
    }

    @org.junit.Test
    public void xs0ys1() {
        assertEquals(7.0, s.findMedianSortedArrays(new int[0], new int[] {7}), 0.001);
    }

    @org.junit.Test
    public void xs0ys4() {
        assertEquals(2.5, s.findMedianSortedArrays(new int[0], new int[] {1, 2, 3, 4}), 0.001);
    }

    @org.junit.Test
    public void xs1ys4() {
        assertEquals(3.0, s.findMedianSortedArrays(new int[] {3}, new int[] {1, 2, 4, 5}), 0.001);
    }

    @org.junit.Test
    public void xs0ys2() {
        assertEquals(5.0, s.findMedianSortedArrays(new int[0], new int[] {4, 6}), 0.001);
    }

    @org.junit.Test
    public void xs1ys2() {
        assertEquals(2.0, s.findMedianSortedArrays(new int[] {2}, new int[] {1, 3}), 0.001);
    }

    @org.junit.Test
    public void xs1ys1() {
        assertEquals(6.5, s.findMedianSortedArrays(new int[] {6}, new int[] {7}), 0.001);
    }

    @org.junit.Test
    public void xs1ysOdd() {
        assertEquals(11.0, s.findMedianSortedArrays(new int[] {5}, new int[] {5, 10, 12, 15, 20}), 0.001);
    }

    @org.junit.Test
    public void xs1ysEven() {
        assertEquals(10.0, s.findMedianSortedArrays(new int[] {10}, new int[] {5, 10, 12, 15}), 0.001);
    }

    @org.junit.Test
    public void xs2ys2() {
        assertEquals(2.5, s.findMedianSortedArrays(new int[] {1, 3}, new int[] {2, 4}), 0.001);
    }

    @org.junit.Test
    public void xs2ysOdd() {
        assertEquals(12.0, s.findMedianSortedArrays(new int[] {2, 16}, new int[]{5, 10, 12, 15, 20}), 0.001);
    }

    @org.junit.Test
    public void xs2ysEven() {
        assertEquals(10.0, s.findMedianSortedArrays(new int[] {9, 10}, new int[]{5, 10, 12, 15}), 0.001);
    }

    @org.junit.Test
    public void generalCase1() {
        int[] xs = {5, 10, 20};
        int[] ys = {13, 16, 25, 80};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }

    @org.junit.Test
    public void generalCase1SwappedArgs() {
        int[] xs = {13, 16, 25, 80};
        int[] ys = {5, 10, 20};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }

    @org.junit.Test
    public void generalCase2() {
        int[] xs = {1, 2, 4, 6, 19, 23, 48, 48, 50};
        int[] ys = {24, 25, 25, 30, 31, 32, 32, 32, 33};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }

    @org.junit.Test
    public void generalCase3() {
        int[] xs = {1, 4, 5, 6};
        int[] ys = {2, 3, 7, 8};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }

    @org.junit.Test
    public void generalCase4() {
        int[] xs = {1, 4, 5, 6};
        int[] ys = {0, 1, 7, 8};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }

    @org.junit.Test
    public void generalCase5() {
        int[] xs = {1, 2, 6, 7};
        int[] ys = {3, 4, 5, 8};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }

    @org.junit.Test
    public void largerCase1() {
        int[] xs = {131,135,195,241,274,288,330,334,342,358,361,391,392,430,470,497,578,627,659,660,756,798,807,819,835,863,869,875,884,912,913,923,928,971,1018,1021,1100,1129,1182,1244,1357,1389,1418,1433,1454,1471,1472,1512,1593,1602,1636,1665,1737,1747,1754,1823,1832,1839,1895,1917,1921,1952,1992,1998,2014,2018,2062,2101,2110,2160,2170,2207,2314,2432,2444,2504,2564,2573,2584,2679,2720,2738,2750,2780,2817,2823,2856,2889,2907,2926,2934,2940,2948,2985,2998,3012,3061,3085,3120,3143,3193,3210,3248,3304,3307,3322,3383,3388,3392,3393,3401,3410,3438,3483,3578,3646,3669,3688,3690,3811,3881,3886,3927,3938,3949,3965,4025,4026,4037,4059,4064,4071,4119,4131,4142,4166,4186,4251,4261,4301,4377,4383,4434,4452,4467,4473,4474,4516,4589,4644,4681,4717,4730,4736,4791,4868,4885,4904,4995,4996,5026,5054,5066,5104,5110,5115,5173,5201,5217,5219,5268,5269,5325,5353,5361,5400,5442,5443,5496,5586,5618,5705,5765,5784,5832,5863,5883,5903,5929,5936,5946,5966,5978,6002,6019,6057,6119,6165,6188,6204,6208,6220,6306,6318,6478,6495,6519,6660,6694,6706,6727,6764,6789,6805,6810,6822,6842,6893,6903,6903,6904,6917,6946,7021,7147,7151,7153,7348,7385,7448,7476,7508,7554,7573,7620,7662,7673,7693,7717,7748,7770,7772,7827,7931,8038,8081,8100,8101,8162,8236,8311,8409,8422,8450,8451,8465,8480,8501,8578,8599,8644,8712,8741,8784,8821,8873,8899,8902,8932,8991,9012,9014,9040,9066,9075,9204,9247,9351,9356,9361,9427,9427,9474,9482,9525,9539,9570,9588,9596,9597,9610,9619,9676,9687,9693,9709,9715,9761,9767,9775,9814,9839,9884,9969,9978,9999,10053,10055,10120,10198,10225,10266,10336,10355,10363,10368,10375,10380,10400,10417,10435,10509,10525,10609,10610,10676,10692,10762,10791,10801,10818,10876,10877,10963,10972,11007,11089,11111,11121,11140,11185,11192,11265,11293,11309,11357,11415,11428,11526,11526,11544,11549,11611,11636,11637,11653,11700,11794,11807,11818,11826,11855,11856,11888,11911,11960,11973,12039,12046,12079,12103,12111,12165,12244,12271,12276,12307,12325,12337,12376,12421,12431,12439,12483,12547,12567,12578,12609,12610,12623,12631,12701,12731,12750,12756,12764,12790,12830,12902,12931,12997,13015,13151,13154,13156,13252,13282,13298,13399,13457,13464,13473,13546,13551,13566,13582,13604,13605,13612,13729,13734,13814,13885,13903,13914,13914,13939,13944,14043,14055,14077,14088,14090,14109,14185,14198,14220,14265,14314,14333,14363,14375,14376,14427,14430,14502,14504,14516,14555,14657,14663,14679,14752,14764,14804,14831,14836,14894,14951,14968,15005,15069,15091,15091,15096,15163,15185,15239,15244,15255,15315,15326,15350,15406,15436,15444,15472,15538,15628,15654,15669,15699,15729,15742,15757,15767,15784,15798,15827,15851,15869,15887,15887,15909,15918,16074,16078,16173,16212,16257,16301,16332,16335,16344,16397,16401,16408,16425,16461,16479,16486,16487,16517,16531,16532,16570,16579,16598,16634,16650,16682,16708,16726,16747,16758,16758,16813,16832,16890,16908,16926,16943,16948,17037,17048,17078,17081,17097,17150,17188,17214,17235,17244,17247,17256,17334,17431,17450,17509,17512,17514,17521,17525,17539,17566,17595,17653,17665,17667,17703,17730,17765,17768,17773,17788,17827,17852,17884,17893,17909,17959,18016,18072,18103,18115,18150,18164,18245,18251,18316,18341,18383,18536,18548,18557,18608,18651,18653,18674,18732,18798,18819,18883,19012,19021,19087,19120,19130,19202,19206,19217,19230,19296,19310,19340,19384,19459,19460,19471,19537,19544,19552,19626,19763,19785,19859,19880,19892,19900,19910,19920,19963,19984,20017,20099,20105,20137,20139,20175,20244,20359,20381,20389,20415,20530,20561,20649,20739,20779,20785,20789,20836,20877,20894,20955,20983,21005,21055,21148,21164,21165,21172,21181,21272,21303,21318,21343,21353,21356,21464,21529,21577,21595,21606,21621,21672,21699,21731,21732,21765,21780,21915,21928,21946,21970,21977,22023,22047,22048,22099,22168,22207,22231,22251,22263,22274,22296,22301,22334,22450,22464,22534,22687,22730,22734,22808,22823,22890,22937,22975,22983,23010,23056,23089,23105,23120,23146,23159,23250,23274,23281,23310,23333,23340,23394,23427,23435,23473,23497,23536,23563,23570,23624,23626,23664,23704,23725,23734,23739,23749,23797,23814,23901,23905,23988,24028,24053,24195,24225,24273,24293,24321,24347,24412,24417,24442,24447,24475,24533,24603,24734,24762,24818,24819,24847,24858,24867,24881,24882,24895,24920,24945,24946,25010,25012,25020,25070,25076,25088,25107,25108,25157,25159,25189,25195,25244,25264,25357,25395,25429,25472,25490,25515,25575,25615,25622,25629,25731,25752,25803,25828,25850,25876,25979,26030,26041,26067,26083,26111,26124,26163,26218,26232,26278,26293,26347,26348,26397,26412,26413,26420,26474,26485,26511,26556,26595,26614,26682,26698,26752,26793,26870,26896,26919,26933,26946,26996,27017,27022,27065,27110,27131,27136,27161,27165,27183,27359,27403,27408,27426,27434,27581,27603,27620,27645,27688,27702,27716,27731,27742,27759,27768,27809,27818,27837,27851,28200,28225,28253,28308,28353,28383,28407,28440,28457,28473,28494,28546,28575,28584,28586,28595,28620,28674,28675,28675,28831,28835,28938,28963,28992,28994,29068,29123,29156,29194,29204,29313,29381,29404,29434,29460,29487,29527,29556,29681,29688,29690,29691,29757,29760,29788,29802,29894,29898,29959,29989,29991,29994,30016,30024,30058,30084,30089,30089,30123,30143,30167,30167,30210,30233,30236,30312,30324,30400,30486,30524,30555,30556,30602,30609,30619,30630,30666,30671,30676,30780,30784,30788,30818,30861,30863,30890,30912,30952,31242,31258,31273,31304,31394,31403,31408,31411,31461,31470,31472,31477,31505,31562,31593,31597,31699,31711,31762,31778,31803,31812,31906,31912,31944,31945,31946,31955,32005,32016,32042,32052,32130,32153,32183,32194,32197,32205,32220,32367,32368,32401,32424,32498,32508,32521,32546,32601,32615,32632,32699,32716,32736,32751,32751};
        int[] ys = {39,99,100,114,149,221,235,238,300,312,381,400,406,457,498,519,521,539,539,573,595,602,610,669,684,695,701,707,781,804,809,817,851,885,896,993,1058,1069,1148,1162,1186,1200,1213,1221,1263,1278,1299,1301,1334,1392,1421,1500,1513,1566,1575,1585,1666,1669,1722,1782,1922,1947,1987,1993,2010,2066,2096,2149,2152,2176,2188,2224,2357,2358,2417,2424,2450,2500,2541,2693,2729,2776,2885,2892,2896,2919,2940,2952,3026,3042,3092,3107,3160,3160,3205,3330,3349,3360,3387,3394,3459,3460,3465,3478,3504,3520,3530,3556,3557,3569,3589,3591,3591,3592,3632,3670,3674,3691,3735,3747,3942,3943,3947,3964,3973,3993,4019,4091,4210,4257,4265,4306,4364,4428,4429,4500,4502,4542,4549,4590,4623,4744,4762,4774,4833,4850,4853,4867,4894,4924,4925,4973,5001,5018,5031,5063,5089,5091,5092,5103,5152,5156,5222,5223,5239,5307,5314,5365,5400,5459,5460,5486,5498,5522,5546,5585,5648,5649,5664,5669,5731,5801,5818,5880,5908,5956,5972,6007,6016,6085,6131,6205,6207,6213,6220,6237,6254,6299,6351,6378,6429,6486,6499,6515,6528,6610,6612,6652,6655,6732,6757,6774,6948,6962,6971,7028,7031,7044,7062,7134,7138,7168,7193,7212,7230,7237,7304,7393,7447,7447,7574,7607,7620,7655,7680,7727,7762,7817,7916,8044,8044,8052,8174,8189,8247,8261,8292,8293,8300,8312,8316,8347,8371,8481,8484,8513,8543,8572,8586,8595,8597,8647,8693,8750,8764,8770,8772,8797,8833,8857,8875,8887,8896,8925,8934,8952,8972,8998,9050,9092,9117,9179,9203,9229,9248,9308,9346,9358,9367,9381,9388,9403,9407,9444,9448,9512,9524,9540,9679,9744,9769,9769,9833,9842,9858,9977,10083,10096,10119,10126,10132,10146,10187,10236,10279,10291,10314,10317,10325,10358,10430,10503,10523,10549,10562,10599,10605,10695,10714,10722,10798,10800,10811,10838,10858,10861,10882,11011,11021,11038,11052,11084,11100,11138,11161,11180,11186,11219,11246,11250,11271,11344,11421,11474,11481,11538,11571,11574,11642,11654,11681,11738,11756,11788,11803,11826,11894,11912,11935,11969,11978,12014,12030,12033,12037,12061,12085,12106,12107,12141,12201,12206,12245,12300,12384,12390,12420,12443,12448,12455,12476,12564,12575,12578,12606,12684,12731,12733,12751,12777,12795,12820,12859,12908,13003,13045,13083,13149,13149,13171,13240,13304,13307,13372,13401,13423,13449,13484,13505,13540,13556,13638,13698,13726,13729,13737,13783,13786,13813,13866,13893,13954,13976,13983,14042,14065,14107,14112,14151,14210,14255,14292,14297,14319,14329,14346,14415,14427,14430,14435,14445,14609,14610,14646,14707,14737,14865,14917,15081,15123,15137,15152,15170,15180,15209,15216,15238,15291,15305,15309,15330,15336,15348,15369,15416,15481,15493,15525,15640,15737,15750,15787,15793,15799,15826,15869,15980,16031,16044,16090,16193,16321,16331,16368,16404,16417,16442,16455,16573,16591,16593,16656,16734,16752,16765,16796,16997,17030,17114,17160,17162,17172,17173,17181,17225,17226,17239,17239,17243,17286,17290,17357,17427,17474,17499,17512,17517,17567,17726,17731,17781,17834,17874,17940,17944,17949,17962,17979,17979,18036,18042,18054,18089,18103,18126,18137,18145,18176,18206,18286,18369,18377,18569,18571,18591,18611,18624,18666,18672,18698,18707,18779,18790,18937,18956,18967,18968,18970,18991,18992,19003,19010,19076,19092,19095,19113,19155,19216,19216,19232,19247,19259,19262,19338,19358,19362,19397,19425,19459,19611,19631,19641,19665,19743,19765,19775,19798,19817,19827,19847,19850,19951,19980,20033,20041,20077,20097,20107,20141,20190,20211,20242,20328,20393,20414,20467,20479,20501,20525,20545,20548,20614,20660,20752,20874,20925,20957,20966,21028,21067,21108,21146,21153,21210,21273,21298,21331,21334,21349,21357,21517,21557,21588,21614,21623,21671,21681,21782,21836,21866,21968,21969,22000,22002,22020,22059,22090,22162,22259,22290,22314,22370,22381,22391,22562,22582,22615,22705,22708,22757,22771,22785,22825,22881,22885,22901,22942,22969,22975,22988,23028,23039,23064,23072,23115,23156,23175,23182,23206,23210,23277,23315,23342,23401,23408,23475,23477,23501,23517,23579,23615,23644,23691,23702,23727,23729,23733,23808,23823,23831,23853,23933,24002,24010,24019,24045,24073,24218,24238,24244,24280,24297,24360,24362,24389,24400,24461,24495,24515,24532,24554,24602,24615,24654,24698,24739,24758,24835,24841,24916,25021,25061,25101,25102,25153,25153,25287,25292,25296,25311,25316,25316,25319,25327,25395,25432,25454,25472,25557,25621,25622,25631,25649,25689,25724,25741,25742,25796,25839,25865,25866,25871,25874,25911,25916,25925,25941,25958,25981,26092,26098,26113,26160,26173,26315,26318,26355,26385,26390,26417,26429,26466,26488,26535,26542,26618,26674,26724,26773,26785,26807,26837,26840,26861,26891,26969,26971,27009,27027,27063,27196,27220,27251,27289,27308,27326,27331,27340,27356,27428,27428,27499,27524,27596,27700,27708,27856,27873,27923,27947,27990,27992,28008,28072,28081,28112,28150,28220,28253,28286,28316,28323,28326,28344,28366,28421,28436,28441,28471,28486,28585,28592,28684,28690,28698,28704,28731,28750,28761,28782,28851,28931,28935,28945,28953,28974,29080,29090,29107,29196,29200,29207,29224,29234,29253,29258,29303,29322,29325,29334,29348,29382,29396,29409,29410,29450,29491,29504,29522,29555,29641,29644,29647,29653,29676,29690,29834,29885,29896,29909,29963,30035,30064,30104,30175,30195,30227,30232,30260,30268,30294,30332,30340,30348,30393,30412,30449,30465,30519,30571,30580,30601,30627,30678,30713,30726,30745,30748,30757,30806,30808,30813,30822,30916,30924,30930,30997,31001,31069,31132,31181,31190,31202,31231,31249,31256,31339,31348,31365,31384,31436,31460,31550,31574,31596,31685,31698,31710,31730,31736,31761,31799,31857,31891,31916,31950,31962,31969,31988,32039,32059,32067,32159,32162,32164,32188,32196,32268,32289,32315,32327,32355,32361,32374,32485,32489,32539,32569,32577,32602,32613,32631,32645,32658,32667,32674,32692,32697,32700,32737};
        assertEquals(Merge.median(Merge.merge(xs, ys)), s.findMedianSortedArrays(xs, ys), 0.001);
    }
}
